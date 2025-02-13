# Telecom Management System

## Overview

The **Telecom Management System** is a user management and billing system that allows both users and admins to manage accounts and balances. This system supports login, user registration, balance view and modification, and admin functionalities. It is designed to handle basic telecom-related functionalities such as user account creation, balance tracking, and administrative actions like modifying user balances.

## Features

- **User Registration:** Allows users to register with a username, password, and a role (user/admin).
- **Login System:** Provides a secure login mechanism for both regular users and administrators.
- **Balance Management:** Users can view their current balance, and administrators can modify the balance for any user.
- **Admin Panel:** Admins have access to additional features, such as viewing and modifying user balances.

## Technologies Used

- **C Programming Language** - The entire system is written in C for simplicity and performance.
- **File Handling** - The system uses file handling to store user data, including usernames, passwords, roles, and balances.
- **Standard Libraries** - The program uses standard C libraries like `stdio.h` and `string.h` for input/output and string manipulation.

## Installation

### Prerequisites

- A C compiler (e.g., GCC)
- A terminal or command prompt

### Steps to Install

1. **Clone the repository:**
   ```git clone https://github.com/EjramWay/Telecom.git


2. **Navigate to the project directory:**
    ``` bash cd telecom-management-system

3. **Compile the C code:**

   ```bash gcc main.c -o telecom_management_system


## Usage

### For Users:
- **Login:** Users can log in with their username and password.
- **View Balance:** Once logged in, users can check their balance.

### For Admins:
- **Admin Login:** Admins can log in with their credentials and manage the balances of other users.
- **Modify Balance:** Admins can add or subtract balances from a user's account.

### Example:
1. Register a new user with a username and password.
2. Log in with the registered username and password.
3. The system will display the balance, which starts at `0.00` for new users.
4. Admins can modify the user's balance by adding or subtracting funds.

## File Structure

- **users.dat**: The file where user details, including usernames, passwords, roles, and balances, are stored.
- **main.c**: The C source code file where all functionalities of the system are implemented.

## Contributing

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-name`).
3. Make your changes and commit them (`git commit -am 'Added feature'`).
4. Push the changes to the branch (`git push origin feature-name`).
5. Create a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.



 
