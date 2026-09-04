Digital Time Capsule

📌 Project Overview

Digital Time Capsule is a C++ console-based application that allows users to create digital capsules containing personal messages, memories, goals, or notes and lock them until a specific future date and time.
The messages are stored in encrypted form and can only be accessed after the unlock time using the correct Master Key.

✨ Features

🔐 Master Key Protection — Enter one Master Key when the program starts.
📦 Create Capsules — Store messages, memories, goals, or notes.
⏳ Time-Based Unlocking — Capsules remain locked until their specified date and time.
🔒 Encryption & Decryption — Messages are encrypted before being stored.
👀 View Capsules — View capsule information and remaining unlock time without seeing the protected message.
🔎 Search Capsules — Search capsules by title, category, or owner.
📤 Export Capsule — Export an individual capsule to a separate file.
📥 Import Capsule — Import an exported capsule on another computer.
💾 Backup — Create a backup copy of all saved capsule data.
♻️ Restore Backup — Restore capsule data if the main file is lost or deleted.
🗑️ Delete Capsule — Remove an existing capsule.
🧪 Unit Tests — Test encryption, dates, and Master Key verification.
💿 File Storage — Capsule information is automatically saved to a file.

🔄 How It Works

Start Program
      ↓
Enter Master Key
      ↓
Load Saved Capsules
      ↓
Main Menu
      ↓
Create Capsule
      ↓
Enter Message & Unlock Date
      ↓
Encrypt Message
      ↓
Save Capsule
      ↓
Wait Until Unlock Time
      ↓
Enter Correct Master Key
      ↓
Decrypt & Display Message
