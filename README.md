# 📦 Inventory Management System

A full-stack inventory management system built with a combination of custom firmware, Node.js backend, and a responsive frontend for real-time tracking, item control, and stock analytics. Designed for small to medium-scale warehouse or office environments.

---

## 🧠 Core Features

- 🗃️ Add, update, delete inventory items
- 📊 Real-time stock tracking and quantity updates
- 🔍 Search and filter inventory
- ⚠️ Low-stock alerts
- 📡 Microcontroller integration for automated input (via Firmware)
- 🖥️ User-friendly dashboard built using HTML/CSS/JS

---

## 🛠️ Tech Stack

| Layer           | Technologies            |
|----------------|-------------------------|
| **Frontend**    | HTML, CSS, JS (in `/template`) |
| **Backend**     | Node.js, Express.js (`server.js`) |
| **IoT / Firmware** | Arduino / Embedded C (in `/Firmware`) |
| **Database**    | JSON-based (assumed) or file storage |
| **Assets**      | `/static` for CSS/JS/img |
| **Desktop Utility** | Additional tools/scripts in `computer_side` |

---

## 📁 Project Structure
inventory-management-system/
├── Firmware/ # Embedded code for microcontroller integration
├── computer_side/ # Scripts for computer-side operations or USB interfacing
├── node_modules/ # Node.js dependencies
├── static/ # Frontend assets (CSS, JS, images)
├── template/ # Frontend HTML templates
├── server.js # Node.js backend server
├── package.json # Project metadata and dependencies
├── package-lock.json # Dependency lock file
└── README.md # Project documentation


---

## 🚀 How to Run the Project

1. **Install dependencies**
   ```bash
   npm install

2. **Start the Server**
   ```bash
   node server.js

3. **Open in Browser**
   ```bash
   http://localhost:3000

4. **Connect Microcontroller**
Upload firmware from the /Firmware folder to your microcontroller using Arduino IDE.

Ensure serial communication is properly synced with the backend (e.g., correct COM port and baud rate).

## 🧪 Future Enhancements
- 🔐 Role-based user login system
- 🧾 Barcode scanner integration
- ☁️ Cloud storage support (MongoDB / Firebase)
- 📈 Analytics dashboard for usage trends
