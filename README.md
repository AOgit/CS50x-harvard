
 # 📘 CS50x — Harvard's Introduction to Computer Science



- ✅ **Completed CS50x** — 2025
- 🏆 **My Certificate:** [https://cs50.harvard.edu/certificates/ea03d1bb-ca25-43b4-8295-855fb668a4e6]
- 📁 **Original submissions (me50):** [https://github.com/me50/AOgit](https://github.com/me50/AOgit)

  

---
Welcome to **CS50x — Harvard's Introduction to Computer Science (2025 edition)**!

This repository contains my complete coursework, exercises, and projects (including the final project) for CS50x taught through edX and Harvard's official curriculum.

> ⚠️ All CS50x problem sets and projects are organized into **branches and tags**. To explore my progress, please check the corresponding branches or tags.
---




## 🚀 About the Course

**CS50x** is an entry‑level course that teaches you how to think algorithmically and solve problems efficiently. It covers fundamentals of computer science and programming using languages such as C, Python, SQL, and JavaScript, alongside essential concepts like algorithms, data structures, memory, and web development.

This repository is a complete log of my journey through the course — from problem sets to my final capstone project.

---



📌 The primary project here is **Weird Length Converter** — a Flask‑based web application that allows users to compare and convert units in a fun & interactive way.

---

## 💡 Project — Weird Length Converter

### 🎬 Video Demo

**Watch the demo here:**
👉 https://youtu.be/SeTML0uMCH0

---
## 📂 Repository Contents

Below you'll find the major sections included in this repository:

```
├── flask_session/      # Flask session data
├── static/             # Static files (CSS, images)
├── templates/          # HTML templates for web apps
├── app.py              # Main Flask application
├── helpers.py          # Helper functions
├── requirements.txt    # Python dependencies
├── weirdcalc.db        # SQLite database
└── README.md           # This file
```

## 📌 Features & Functionality

### 🔍 Core Features

| Feature | Description |
|---------|-------------|
| Length Conversion | Convert one object's length into the equivalent of another. |
| Custom Objects | Users can add, edit, and delete objects with custom lengths. |
| User Accounts | Registration & login system with secure session management. |
| Instant Feedback | JavaScript updates conversion results without reloading. |

---

## 🧠 Technologies Used

| Layer | Technologies |
|-------|--------------|
| Backend | Python, Flask |
| Frontend | HTML, CSS, JavaScript |
| Database | SQLite3 |
| Dependencies | See `requirements.txt` |

---

## 🛠 Application Workflow

### User Authentication

- **Registration**: Create account with username & password.
- **Login**: Access converter dashboard upon successful login.
- **Session Management**: Users remain logged in to manage custom objects.

### Conversion Logic

1. Select an object as the *source* and one as the *target*.
2. Input a quantity for the source.
3. View results instantly as equivalent units of the target object.

### Custom Object Management

- Users can **add, edit, or delete** custom objects.
- Objects are stored with names and length values (in meters).

---

## 📁 Detailed File Breakdown

### 🧩 Flask Backend

- **app.py** — Main application logic — routes, session checks, and CRUD operations.
- **helpers.py** — Utility functions (e.g., `apology()` for error messages and `login_required()` decorator).
- **requirements.txt** — Lists all Python packages required to run the app locally.

### 🖼 Frontend

- **templates/** — HTML files for rendering UI pages (login, register, converter, etc.).
- **static/** — Contains CSS styles and image assets for the web interface.

### 🗃 Database

- **weirdcalc.db** — Stores user accounts and custom object data in SQLite format.

---

## 📌 Installation & Setup

To get this project running locally:

**1. Clone the repo:**
```bash
git clone https://github.com/AOgit/CS50x.git
cd CS50x
```

**2. Create a virtual environment:**
```bash
python3 -m venv venv
source venv/bin/activate   # macOS/Linux
venv\Scripts\activate      # Windows
```

**3. Install dependencies:**
```bash
pip install -r requirements.txt
```

**4. Run the application:**
```bash
python app.py
```

**5.** Open your browser at `http://localhost:5000`

---

## 🧪 Usage Examples

```python
# Add a new object:
POST /add-object
{"name": "Eiffel Tower", "length": 324}

# Convert 3 parrots to Everests:
GET /convert?from=parrot&to=everest&amount=3
```

---

## 📈 Future Enhancements

Potential improvements I plan to work on:

- Add measurement categories (units, distances, weights)
- Support mobile‑friendly layout
- Add internationalization (multilingual UI)
- Deploy to a cloud hosting provider (e.g., Render / Heroku)

---

## ⚖️ License

This repository is open source and licensed under the MIT License. Feel free to use and adapt it under terms of the license.

---

## 🧑‍💻 Acknowledgments

- Harvard University & CS50 Staff for an amazing course.
- All mentors, peers, and online communities who helped me throughout CS50.

---

## 📬 Contact

GitHub: https://github.com/AOgit
