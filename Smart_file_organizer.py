import os
import shutil
import time
from datetime import datetime, timedelta

# Customize these paths
SOURCE_DIR = os.path.expanduser("~/Downloads")  # Change if needed
TARGET_DIR = os.path.expanduser("~/Organized")

# File categories
FILE_CATEGORIES = {
    "Images": [".png", ".jpg", ".jpeg", ".gif"],
    "Documents": [".pdf", ".docx", ".txt", ".pptx", ".xlsx"],
    "Videos": [".mp4", ".mov", ".avi"],
    "Archives": [".zip", ".rar", ".7z", ".tar"],
    "Others": []
}

# Time range for recent
RECENT_DAYS = 5

def get_file_category(filename):
    ext = os.path.splitext(filename)[1].lower()
    for category, extensions in FILE_CATEGORIES.items():
        if ext in extensions:
            return category
    return "Others"

def organize_file(file_path):
    access_time = os.path.getatime(file_path)
    days_old = (datetime.now() - datetime.fromtimestamp(access_time)).days
    category = get_file_category(file_path)

    time_folder = "Recent" if days_old <= RECENT_DAYS else "Old"
    dest_folder = os.path.join(TARGET_DIR, time_folder, category)

    os.makedirs(dest_folder, exist_ok=True)
    try:
        shutil.move(file_path, os.path.join(dest_folder, os.path.basename(file_path)))
        print(f"Moved: {file_path} → {dest_folder}")
    except Exception as e:
        print(f"Error moving {file_path}: {e}")

def run_organizer():
    if not os.path.exists(SOURCE_DIR):
        print("Source directory does not exist.")
        return

    for item in os.listdir(SOURCE_DIR):
        full_path = os.path.join(SOURCE_DIR, item)
        if os.path.isfile(full_path):
            organize_file(full_path)

    print("\n✅ All files organized successfully!")

# Run it
run_organizer()
