import time
import tkinter as tk
import numpy as np  # Добавьте эту строку
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

class LineDrawingApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Line Drawing Algorithms")

        self.frame = tk.Frame(self.root, bg='white')
        self.frame.pack(fill=tk.BOTH, expand=True)

        self.fig = Figure(figsize=(5, 4), dpi=100)
        self.ax = self.fig.add_subplot(111)
        self.canvas = FigureCanvasTkAgg(self.fig, master=self.frame)
        self.canvas.get_tk_widget().pack(fill=tk.BOTH, expand=True)
        self.canvas.draw()

        # Group Start and End Points
        self.start_frame = tk.Frame(self.root)
        self.start_frame.pack(pady=5)
        self.label_x1 = tk.Label(self.start_frame, text="Start X:")
        self.label_x1.pack(side=tk.LEFT)
        self.entry_x1 = tk.Entry(self.start_frame)
        self.entry_x1.pack(side=tk.LEFT)

        self.label_y1 = tk.Label(self.start_frame, text="Start Y:")
        self.label_y1.pack(side=tk.LEFT)
        self.entry_y1 = tk.Entry(self.start_frame)
        self.entry_y1.pack(side=tk.LEFT)

        self.end_frame = tk.Frame(self.root)
        self.end_frame.pack(pady=5)
        self.label_x2 = tk.Label(self.end_frame, text="End X:")
        self.label_x2.pack(side=tk.LEFT)
        self.entry_x2 = tk.Entry(self.end_frame)
        self.entry_x2.pack(side=tk.LEFT)

        self.label_y2 = tk.Label(self.end_frame, text="End Y:")
        self.label_y2.pack(side=tk.LEFT)
        self.entry_y2 = tk.Entry(self.end_frame)
        self.entry_y2.pack(side=tk.LEFT)

        # Execution Time
        self.label_execution_time = tk.Label(self.root, text="Execution Time:")
        self.label_execution_time.pack(pady=5)

        # Buttons
        self.button_plot_bresenham = tk.Button(self.root, text="Plot Bresenham", command=self.plot_bresenham)
        self.button_plot_bresenham.pack(side=tk.LEFT, padx=5)

        self.button_plot_bresenham_smooth = tk.Button(self.root, text="Plot Smooth Bresenham", command=self.plot_bresenham_smooth)
        self.button_plot_bresenham_smooth.pack(side=tk.LEFT, padx=5)

        self.button_plot_dda = tk.Button(self.root, text="Plot DDA", command=self.plot_dda)
        self.button_plot_dda.pack(side=tk.LEFT, padx=5)

        self.button_plot_dda_smooth = tk.Button(self.root, text="Plot Smooth DDA", command=self.plot_dda_smooth)
        self.button_plot_dda_smooth.pack(side=tk.LEFT, padx=5)

        self.button_plot_step_by_step = tk.Button(self.root, text="Plot Step by Step Bresenham", command=lambda: self.plot_step_by_step(self.bresenham))
        self.button_plot_step_by_step.pack(side=tk.LEFT, padx=5)

        self.button_plot_castel_pitve = tk.Button(self.root, text="Castel-Pitve", command=self.plot_castel_pitve)
        self.button_plot_castel_pitve.pack(side=tk.LEFT)

    def plot_step_by_step(self, algorithm):
        x1 = int(self.entry_x1.get())
        y1 = int(self.entry_y1.get())
        x2 = int(self.entry_x2.get())
        y2 = int(self.entry_y2.get())

        points = algorithm(x1, y1, x2, y2)
        for i, point in enumerate(points):
            self.ax.clear()
            self.ax.plot([x1, point[0]], [y1, point[1]], 'ro-')
            self.ax.set_title(f"{algorithm.__name__} Line Algorithm (Step {i + 1})")
            self.ax.set_xlabel('X')
            self.ax.set_ylabel('Y')
            self.ax.grid(True)
            self.canvas.draw()
            self.root.update()
            time.sleep(0.1)  # добавьте задержку между шагами

    def plot_castel_pitve(self, n=10):
        x1 = int(self.entry_x1.get())
        y1 = int(self.entry_y1.get())
        x2 = int(self.entry_x2.get())
        y2 = int(self.entry_y2.get())

        t = np.linspace(0, 1, n + 1)
        points = []
        for ti in t:
            x = (1 - ti) ** 3 * x1 + 3 * (1 - ti) ** 2 * ti * x1 + 3 * (1 - ti) * ti ** 2 * x2 + ti ** 3 * x2
            y = (1 - ti) ** 3 * y1 + 3 * (1 - ti) ** 2 * ti * y1 + 3 * (1 - ti) * ti ** 2 * y2 + ti ** 3 * y2
            points.append((x, y))

        self.ax.clear()
        x_coords = [point[0] for point in points]
        y_coords = [point[1] for point in points]
        self.ax.plot(x_coords, y_coords, 'ro-')
        self.ax.set_title("Castel-Pitve Algorithm")
        self.ax.set_xlabel('X')
        self.ax.set_ylabel('Y')
        self.ax.grid(True)
        self.canvas.draw()

    def plot_smooth_line(self, algorithm):
        x1 = int(self.entry_x1.get())
        y1 = int(self.entry_y1.get())
        x2 = int(self.entry_x2.get())
        y2 = int(self.entry_y2.get())

        points = algorithm(x1, y1, x2, y2)
        x_coords = [point[0] for point in points]
        y_coords = [point[1] for point in points]

        smooth_x_coords, smooth_y_coords = [], []
        for i in range(len(x_coords) - 1):
            smooth_x_coords.append(x_coords[i])
            smooth_y_coords.append(y_coords[i])
            x_diff = x_coords[i + 1] - x_coords[i]
            y_diff = y_coords[i + 1] - y_coords[i]
            for j in range(1, 10):
                smooth_x_coords.append(x_coords[i] + j * x_diff / 10)
                smooth_y_coords.append(y_coords[i] + j * y_diff / 10)

        x_coords, y_coords = smooth_x_coords, smooth_y_coords

        self.ax.clear()
        self.ax.plot(x_coords, y_coords, 'ro-')
        self.ax.set_title(f"{algorithm.__name__} Line Algorithm (Smooth)")
        self.ax.set_xlabel('X')
        self.ax.set_ylabel('Y')
        self.ax.grid(True)
        self.canvas.draw()

    def bresenham(self, x1, y1, x2, y2):
        start_time = time.time()

        dx = abs(x2 - x1)
        dy = abs(y2 - y1)
        x, y = x1, y1
        sx = -1 if x1 > x2 else 1
        sy = -1 if y1 > y2 else 1

        if dx < dy:
            dx, dy = dy, dx
            sx, sy = sy, sx

        err = dx / 2.0
        points = []

        for _ in range(dx + 1):
            points.append((x, y))
            err -= dy
            if err < 0:
                y += sy
                err += dx
            x += sx

        execution_time = time.time() - start_time
        self.label_execution_time.config(text="Execution Time: {:.6f} seconds".format(execution_time))

        return points

    def dda(self, x1, y1, x2, y2):
        start_time = time.time()

        dx = x2 - x1
        dy = y2 - y1
        steps = max(abs(dx), abs(dy))

        x_incr = dx / steps
        y_incr = dy / steps

        points = []
        for _ in range(steps):
            points.append((round(x1), round(y1)))
            x1 += x_incr
            y1 += y_incr

        execution_time = time.time() - start_time
        self.label_execution_time.config(text="Execution Time: {:.6f} seconds".format(execution_time))

        return points

    def plot_algorithm(self, algorithm, smooth=False):
        x1 = int(self.entry_x1.get())
        y1 = int(self.entry_y1.get())
        x2 = int(self.entry_x2.get())
        y2 = int(self.entry_y2.get())

        points = algorithm(x1, y1, x2, y2)
        x_coords = [point[0] for point in points]
        y_coords = [point[1] for point in points]

        if smooth:
            smooth_x_coords, smooth_y_coords = [], []
            for i in range(len(x_coords) - 1):
                smooth_x_coords.append(x_coords[i])
                smooth_y_coords.append(y_coords[i])
                x_diff = x_coords[i + 1] - x_coords[i]
                y_diff = y_coords[i + 1] - y_coords[i]
                for j in range(1, 10):
                    smooth_x_coords.append(x_coords[i] + j * x_diff / 10)
                    smooth_y_coords.append(y_coords[i] + j * y_diff / 10)

            x_coords, y_coords = smooth_x_coords, smooth_y_coords

        self.ax.clear()
        self.ax.plot(x_coords, y_coords, 'ro-')
        self.ax.set_title(f"{algorithm.__name__} Line Algorithm {'(Smooth)' if smooth else ''}")
        self.ax.set_xlabel('X')
        self.ax.set_ylabel('Y')
        self.ax.grid(True)

        self.canvas.draw()

    def plot_bresenham(self):
        self.plot_algorithm(self.bresenham)

    def plot_bresenham_smooth(self):
        self.plot_algorithm(self.bresenham, smooth=True)

    def plot_dda(self):
        self.plot_algorithm(self.dda)

    def plot_dda_smooth(self):
        self.plot_algorithm(self.dda, smooth=True)


root = tk.Tk()
app = LineDrawingApp(root)
root.mainloop()