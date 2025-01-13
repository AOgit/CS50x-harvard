import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required

# Configure application
app = Flask(__name__)

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///weirdcalc.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
# @login_required
def index():
    """Show default und users units"""
    user_id = session.get("user_id")
    if user_id:
        units = db.execute(
            "SELECT * FROM units WHERE user_id IN(1, ?) ORDER BY user_id DESC, name", user_id)
    else:
        units = db.execute("SELECT * FROM units WHERE user_id = 1 ORDER BY user_id DESC, name")
    return render_template("index.html", units=units)


@app.route("/add", methods=["GET", "POST"])
@login_required
def add():
    """Add new units to list"""
    user_id = session.get("user_id")
    if request.method == "POST":
        name = request.form.get("name")
        if not name:
            return apology("Invalid name")
        try:
            length = float(request.form.get("length"))
        except:
            return apology("length must be a positive number", 400)

        if length <= 0:
            return apology("length must be a positive number", 400)

        db.execute("INSERT INTO units (user_id, name, length) VALUES(?, ?, ?)", user_id, name, length)
        flash("The unit was added")
        return redirect("/")
    else:
        return render_template("edit.html", unit={}, title="Add a new unit", action="/add")


@app.route("/edit", methods=["GET", "POST"])
@login_required
def edit():
    """Edit privat units"""
    user_id = session.get("user_id")
    if request.method == "POST":
        unit_id = request.form.get("unit_id")
        if not unit_id:
            return apology("Invalid unit")

        name = request.form.get("name")
        length = request.form.get("length")
        if not name or not length:
            unit = db.execute("SELECT * FROM units WHERE id = ?", unit_id)
            return render_template("edit.html", unit=unit[0], title="Edit unit", action="/edit")

        try:
            length = float(length)
        except:
            return apology("length must be a positive number", 400)

        if length <= 0:
            return apology("length must be a positive number", 400)

        try:
            n = db.execute(
                "UPDATE units SET name = ?,  length = ? WHERE user_id = ? AND id = ?", name, length, user_id, unit_id)
        except:
            return apology("SQL UPDATE request error!", 400)
        if n == 1:
            flash("The unit has been edited")
        else:
            flash("Schiit Happened :(")
        return redirect("/")
    else:
        units = db.execute("SELECT * FROM units WHERE user_id = ?", user_id)
        if not units:
            return apology("You haven't added any units yet", 400)
        return render_template("choose.html", units=units, title="Edit unit", action="/edit", button="Edit unit")


@app.route("/del", methods=["GET", "POST"])
@login_required
def rem():
    """Sell shares of stock"""
    user_id = session.get("user_id")
    if request.method == "POST":
        unit_id = request.form.get("unit_id")
        if not unit_id:
            return apology("Invalid unit")
        try:
            db.execute("DELETE FROM units WHERE user_id = ? AND id = ?", user_id, unit_id)
        except ValueError:
            return apology("Unit not exists", 400)
        except:
            return apology("SQL DELETE request error!", 400)
        flash("The unit has been removed")
        return redirect("/")
    else:
        units = db.execute("SELECT * FROM units WHERE user_id = ?", user_id)
        if not units:
            return apology("You haven't added any units yet", 400)
        return render_template("choose.html", units=units, title="Delete unit", action="/del", button="Delete unit")


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
        return redirect(request.form.get("next"))

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

        hash = generate_password_hash(password)
        try:
            user_id = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        except ValueError:
            return apology("User with this name already exists", 400)
        except:
            return apology("SQL INSERT user request error", 400)

        # Remember which user has logged in
        session["user_id"] = user_id
        return redirect("/")
    else:
        return render_template("register.html")


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

        flash("The password was successfully changed")
        return redirect("/")
    else:
        return render_template("change_password.html")
