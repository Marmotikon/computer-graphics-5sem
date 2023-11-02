import cv2
import numpy as np
import tkinter as tk
from tkinter import filedialog
import os

def bernsen_thresholding(image, e=15, r=15):
    processed_image = np.copy(image)
    half_r = r // 2
    for x in range(half_r, image.shape[1] - half_r):
        for y in range(half_r, image.shape[0] - half_r):
            pixel_values = []
            for i in range(x - half_r, x + half_r + 1):
                for j in range(y - half_r, y + half_r + 1):
                    pixel_values.append(image[j, i])

            jlow = np.min(pixel_values)
            jhigh = np.max(pixel_values)
            threshold = (jhigh - jlow) / 2

            if threshold <= e:
                processed_image[y, x] = 0
            else:
                processed_image[y, x] = 255

    return processed_image

def niblack_thresholding(image, r=15, k=-0.2):
    processed_image = np.copy(image)
    half_r = r // 2
    for x in range(half_r, image.shape[1] - half_r):
        for y in range(half_r, image.shape[0] - half_r):
            neighborhood = image[y - half_r:y + half_r + 1, x - half_r:x + half_r + 1]
            mean_value = np.mean(neighborhood)
            std_deviation = np.std(neighborhood)
            threshold = mean_value + k * std_deviation
            if image[y, x] <= threshold:
                processed_image[y, x] = 0
            else:
                processed_image[y, x] = 255

    return processed_image

def adaptive_thresholding(image, constant=2 / 3, block_size=11):
    processed = cv2.adaptiveThreshold(image, 255, cv2.ADAPTIVE_THRESH_MEAN_C, cv2.THRESH_BINARY, block_size, 1 / constant)
    return processed

def logarithmic_transformation(image):
    max_value = np.max(image)
    transformed = 255 * (np.log1p(image) / np.log1p(max_value))
    transformed = np.round(transformed).astype(np.uint8)
    return transformed

def log_sharpen(image, alpha=1):
    log_kernel = np.array(
        [[0, 0, -1, 0, 0],
         [0, -1, -2, -1, 0],
         [-1, -2, 16, -2, -1],
         [0, -1, -2, -1, 0],
         [0, 0, -1, 0, 0]], dtype=np.float32)
    laplacian_of_gaussian = cv2.filter2D(image, cv2.CV_64F, log_kernel)
    laplacian_of_gaussian = np.clip(laplacian_of_gaussian, 0, 255)
    laplacian_of_gaussian = laplacian_of_gaussian.astype(np.uint8)
    image = image.astype(np.uint8)
    sharpened_image = cv2.add(image, alpha * laplacian_of_gaussian, dtype=cv2.CV_8U)
    sharpened_image = np.clip(sharpened_image, 0, 255).astype(np.uint8)
    return sharpened_image

def laplacian_sharpen(image):
    laplacian_kernel = np.array(
        [[0, -1, 0],
         [-1, 5, -1],
         [0, -1, 0]], dtype=np.float32)
    sharpened_image = cv2.filter2D(image, -1, laplacian_kernel)
    sharpened_image = np.clip(sharpened_image, 0, 255)
    sharpened_image = sharpened_image.astype(np.uint8)
    return sharpened_image

def select_input_directory():
    current_directory = os.getcwd()
    input_directory = filedialog.askdirectory(initialdir=current_directory, title="Select Input Directory")
    if input_directory:
        input_entry.delete(0, tk.END)
        input_entry.insert(0, os.path.relpath(input_directory, current_directory))

def select_output_directory():
    current_directory = os.getcwd()
    output_directory = filedialog.askdirectory(initialdir=current_directory, title="Select Output Directory")
    if output_directory:
        output_entry.delete(0, tk.END)
        output_entry.insert(0, os.path.relpath(output_directory, current_directory))

def process_images():
    current_directory = os.getcwd()
    input_directory = os.path.join(current_directory, input_entry.get().replace('/', '\\'))
    output_directory = os.path.join(current_directory, output_entry.get().replace('/', '\\'))

    methods = [
        niblack_thresholding,

        # laplacian_sharpen,
        # log_sharpen
    ]

    for method in methods:
        method_output_directory = os.path.join(output_directory, method.__name__)
        os.makedirs(method_output_directory, exist_ok=True)

        image_files = os.listdir(input_directory)
        for image_file in image_files:
            if image_file.endswith('.png') or image_file.endswith('.jpg'):
                image_path = os.path.join(input_directory, image_file)
                image = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
                processed_image = method(image)
                output_image_path = os.path.join(method_output_directory, image_file)
                cv2.imwrite(output_image_path, processed_image)
        print(method.__name__, " Completed\n")

    print("Processing complete!")

# Create the main window
root = tk.Tk()
root.title("Image Processing App")

# Functionality Frame
functionality_frame = tk.Frame(root, padx=10, pady=10)
functionality_frame.pack()

# Input Directory Section
input_label = tk.Label(functionality_frame, text="Input Directory:", fg="blue")
input_label.grid(row=0, column=0, padx=5, pady=5, sticky="w")

input_entry = tk.Entry(functionality_frame, width=40)
input_entry.grid(row=0, column=1, padx=5, pady=5)

input_button = tk.Button(functionality_frame, text="Select", command=select_input_directory, fg="green")
input_button.grid(row=0, column=2, padx=5, pady=5)

# Output Directory Section
output_label = tk.Label(functionality_frame, text="Output Directory:", fg="blue")
output_label.grid(row=1, column=0, padx=5, pady=5, sticky="w")

output_entry = tk.Entry(functionality_frame, width=40)
output_entry.grid(row=1, column=1, padx=5, pady=5)

output_button = tk.Button(functionality_frame, text="Select", command=select_output_directory, fg="green")
output_button.grid(row=1, column=2, padx=5, pady=5)

# Image Processing Section
process_button = tk.Button(root, text="Process Images", command=process_images, bg="yellow", fg="black")
process_button.pack(pady=10)

# Run the application
root.mainloop()
