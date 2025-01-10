import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    user_id = session.get("user_id")
    rows = db.execute(
        "SELECT symbol, SUM(shares) AS shares FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", user_id)
    total = 0
    stocks = []
    for row in rows:
        info = lookup(row["symbol"])
        amount = row["shares"] * info["price"]
        stocks.append({"symbol": row["symbol"], "shares": row["shares"],
                      "price": info["price"], "amount": amount})
        total += amount

    balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    total += balance[0]["cash"]
    return render_template("index.html", stocks=stocks, cash=balance[0]["cash"], total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        info = lookup(request.form.get("symbol"))
        if not info:
            return apology("Invalid symbol")
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Shares must be a positive number", 400)

        if shares <= 0:
            return apology("Shares must be a positive number", 400)

        user_id = session.get("user_id")
        balance = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        amount = info["price"] * shares
        rest = balance[0]["cash"] - amount
        if rest >= 0:
            db.execute("UPDATE users SET cash = ? WHERE id = ?", rest, user_id)
            db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES(?, ?, ?, ?)",
                       user_id, info["symbol"], shares, info["price"])
            flash("Bought!")
            return redirect("/")
        else:
            return apology("Can't afford")

    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    user_id = session.get("user_id")
    rows = db.execute("SELECT * FROM transactions WHERE user_id = ? ORDER BY id ASC", user_id)
    return render_template("history.html", stocks=rows)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if symbol:
            info = lookup(symbol)
            if info:
                return render_template("quoted.html", info=info)
            else:
                return apology("Information about this stock was not found", 400)
        else:
            return apology("Enter stock symbol", 400)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        """Register user"""
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not username:
            return apology("Please, specify the Username", 400)
        if not password or not confirmation:
            return apology("Please, specify the Password and Confirmation", 400)
        if password != confirmation:
            return apology("Password not equal Confirmation", 400)

        # rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        # if len(rows):
        #     return apology("User with this name already exists", 403)

        hash = generate_password_hash(password)
        try:
            user_id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        except ValueError:
            return apology("User with this name already exists", 400)
        except:
            return apology("SQL INSERT user request error!", 400)

        # Remember which user has logged in
        session["user_id"] = user_id
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session.get("user_id")
    if request.method == "POST":
        symbol = request.form.get("symbol")
        if not symbol:
            flash("Choose ticker!")
            return redirect("/sell")
        info = lookup(symbol)
        if not info:
            return apology("Invalid symbol")
        shares = int(request.form.get("shares"))
        if shares <= 0:
            return apology("Shares must be a positive number")

        rows = db.execute(
            "SELECT SUM(shares) AS sum FROM transactions WHERE user_id = ? AND symbol = ?", user_id, info["symbol"])
        quantity = rows[0]["sum"]
        if quantity >= 0 and quantity >= shares:
            amount = info["price"] * shares
            db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", amount, user_id)
            db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES(?, ?, ?, ?)",
                       user_id, info["symbol"], shares * (-1), info["price"])
            flash("Sold!")
            return redirect("/")
        else:
            return apology("Can't afford")

    else:
        tickers = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", user_id)
        return render_template("sell.html", tickers=tickers)


@app.route("/change_password", methods=["GET", "POST"])
@login_required
def change_password():
    user_id = session.get("user_id")
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure password was submitted
        old_password = request.form.get("old_password")
        new_password = request.form.get("new_password")
        if not old_password:
            return apology("must provide Old password", 403)
        elif not new_password:
            return apology("must provide New password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE id = ?", user_id)

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], old_password):
            return apology("invalid Old password", 403)

        hash = generate_password_hash(new_password)
        try:
            user_id = db.execute("UPDATE users SET hash = ? WHERE id = ?", hash, user_id)
        except ValueError:
            return apology("User with this ID not exists??", 400)
        except:
            return apology("SQL UPDATE password request error!", 400)

        flash("The password was successfully changed!")
        return redirect("/")
    else:
        return render_template("change_password.html")
