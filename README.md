
# Weird Length Converter
#### Video Demo:  https://youtu.be/SeTML0uMCH0

**Weird Length Converter** is a fun and educational web application designed to compare the lengths of different objects. It allows users to convert the length of one object (e.g., a parrot) into the equivalent length of another (e.g., Mount Everest). The application supports custom objects, enabling users to add their own items by specifying their lengths in meters.

---

## Features

1. **Length Conversion**:
   - Users can select two items from predefined lists and calculate how many times one item's length fits into another's.
   - The conversion is instantaneous, thanks to JavaScript.

2. **Custom Object Management**:
   - Users can add new objects by specifying their names and lengths in meters.
   - Custom objects appear in the selection lists for future conversions.
   - Objects can also be edited or deleted.

3. **Instant Feedback**:
   - The application utilizes JavaScript to dynamically update conversion results without reloading the page.

4. **User Authentication**:
   - Secure user login and registration system to ensure that custom objects are associated with specific users.
   - Password management functionality (change passwords) is available.

5. **Interactive Design**:
   - The application uses intuitive forms and dropdown menus for an easy user experience.
   - A colorful, engaging theme with graphics enhances the fun and playful nature of the app.

---

## Technologies Used

- **Frontend**:
  - HTML
  - CSS (Custom styles for a visually appealing layout)
  - JavaScript (Handles dynamic updates and dropdown interactivity)

- **Backend**:
  - Python (Flask framework powers the server-side logic)

- **Database**:
  - SQLite3 (Stores user information and object data)

---

## Application Workflow

### User Authentication
- **Registration**:
  - Users provide a username and password to create an account.
  - Passwords are hashed and stored securely.
- **Login**:
  - After successful login, users can access the conversion tool and manage custom objects.
- **Session Management**:
  - Sessions are handled securely using Flask's session functionality. Only logged-in users can access specific pages (e.g., add, edit, delete objects).

### Conversion Logic
- The main conversion tool is located on the homepage (`index.html`):
  - Users select two items (e.g., "parrot" and "Everest") from dropdown menus.
  - Input a quantity (e.g., 1 parrot).
  - The conversion result (e.g., "1 parrot ≈ 0.0000146912 Everest") is calculated based on the ratio of their lengths (stored in meters) and displayed instantly using JavaScript.

### Custom Object Management
- **Add Object**:
  - Users can add a new object by specifying its name and length in meters.
  - The backend validates the input and stores the object in the database.
- **Edit/Delete Object**:
  - Users can modify or remove objects they have added.
  - Changes are reflected immediately in the dropdown lists for conversions.

### Apology/Error Handling
- The `apology` function in `helpers.py` provides custom error messages when something goes wrong. These messages are displayed on the `apology.html` template.


---
## File Structure

```
project/
├── flask_session/          # Directory for Flask session data
├── static/                 # Static files (CSS, images, etc.)
│   ├── favicon.ico         # Favicon for the website
│   ├── I_heart_validator.png # Decorative/branding image
│   ├── styles.css          # Custom CSS styles for the website
│   ├── wierdcalc.png       # Main banner/image used on the site
├── templates/              # HTML templates for Flask
│   ├── apology.html        # Template for displaying error messages
│   ├── change_password.html # Template for changing user password
│   ├── choose.html         # Template for selecting objects for editing and delete
│   ├── edit.html           # Template for adding new and editing existing objects
│   ├── index.html          # Main template for conversions
│   ├── layout.html         # Base template for consistent layout
│   ├── login.html          # Template for user login
│   ├── register.html       # Template for user registration
├── app.py                  # Main Flask application file
├── helpers.py              # Helper functions for the Flask app
├── README.md               # Project documentation (this file)
├── requirements.txt        # Python dependencies for the project
├── weirdcalc.db            # SQLite database file for storing data
```

---

## Code Structure

### **Key Files**

#### Backend (Python)
- `app.py`:
  - Handles all routes (e.g., `/`, `/add`, `/edit`, `/delete`).
  - Implements CRUD operations for objects using SQLite3.
  - Ensures session management and user-specific operations.
- `helpers.py`:
  - Contains helper functions, including:
    - `apology`: Displays error messages.
    - `login_required`: Decorator that restricts access to certain routes for logged-in users.

#### Frontend (HTML/CSS/JavaScript)
- **Templates**:
  - Located in the `templates/` directory.
  - Includes pages for login, registration, conversion, and object management.
  - `layout.html`: A base template for consistent design across pages.
- **Static Files**:
  - CSS (`styles.css`): Provides a colorful and engaging design.
  - Bootstrap 5.3.3 is used to ensure a responsive and modern design, providing pre-styled components and utilities for building an aesthetically pleasing user interface.
  - JavaScript: Enables instant updates for conversions and dropdown interactivity.

#### Database
- `weirdcalc.db`:
  - Contains tables for:
    - `users`: Stores user credentials.
    - `units`: Stores object names and lengths (associated with user IDs).

---

## Example Usage

1. **Convert Lengths**:
   - Select "parrot" from the "From" dropdown and "Everest" from the "Into" dropdown.
   - Enter a quantity (e.g., `1`).
   - View the result: "1 parrot ≈ 0.0000146912 Everest."

2. **Add a Custom Object**:
   - Navigate to the "Add Unit" page.
   - Enter "Great Wall of China" and its length in meters (e.g., `21196`).
   - Use it for future conversions!

---

## Future Enhancements

- Add unit categories (e.g., animals, landmarks) for better organization.
- Support for additional measurement types (e.g., weight, volume).
- Multi-language support for international users.

---

Enjoy converting the weirdest lengths with **Weird Length Converter**! 🦜🌏

---
