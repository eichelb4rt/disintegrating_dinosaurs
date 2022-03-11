import imageio
import numpy as np
from tkinter import Button, Canvas, Tk
from tkinter.messagebox import showinfo

PIXELS_IN_CELL = 32
BACKGROUND_COLOUR = "black"
FILL_COLOUR = "white"
GRID_COLOUR = "gray"
OUTPUT_PATH = "form_image.png"


class Cell:
    def __init__(self, canvas: Canvas, x: int, y: int):
        self.x = x
        self.y = y
        self.canvas = canvas
        self.fill(BACKGROUND_COLOUR)

    def fill(self, colour: str):
        self.colour = colour
        # draw a rectangle filled with the colour, outline is gray
        self.canvas.create_rectangle(PIXELS_IN_CELL * self.x, PIXELS_IN_CELL * self.y, PIXELS_IN_CELL * (
            self.x + 1), PIXELS_IN_CELL * (self.y + 1), fill=colour, width=1, outline=GRID_COLOUR)
    
    def get_colour(self) -> int:
        if self.colour == FILL_COLOUR:
            return 255
        return 0

class Grid:
    def __init__(self, canvas: Canvas, width: int, height: int):
        self.canvas = canvas
        self.width = width
        self.height = height
        self.cells = [[Cell(self.canvas, x, y) for x in range(self.width)] for y in range(self.height)]
        
    def set_pixel(self, x: int, y: int, colour: str):
        self.cells[y][x].fill(colour)
        
    def get_pixel(self, x: int, y: int):
        return self.cells[y][x].value
    
    def to_values(self):
        colours = [[self.cells[y][x].get_colour() for x in range(self.width)] for y in range(self.height)]
        return np.array(colours, dtype=np.uint8)


class MyApplication:
    def __init__(self, width, height):
        self.width = width
        self.height = height

        # creater a tkinter window
        self.window = Tk()
        self.window.title("Draw Form")

        # add a canvas
        self.canvas = Canvas(self.window, width=PIXELS_IN_CELL *
                             width, height=PIXELS_IN_CELL * height, bg=BACKGROUND_COLOUR)
        self.canvas.grid(column=0, row=0, columnspan=1)
        
        # add a grid of cells
        self.grid = Grid(self.canvas, width, height)

        # add a save button
        self.save_button = Button(
            self.window, text="save", height=2, cursor="hand2", command=self.save_action)
        self.save_button.grid(column=0, row=1, sticky="ew")

        # bind button presses to actions
        # left click
        self.canvas.bind("<Button-1>", self.draw_action)
        self.canvas.bind("<B1-Motion>", self.draw_action)
        # right click
        self.canvas.bind("<Button-3>", self.erase_action)
        self.canvas.bind("<B3-Motion>", self.erase_action)

    def start(self):
        self.window.mainloop()

    def save_action(self):
        image = self.grid.to_values()
        imageio.imsave(OUTPUT_PATH, image)
        showinfo(message="Image saved!")
    
    def out_of_bounds(self, x, y):
        return x < 0 or x >= self.width or y < 0 or y >= self.height

    def draw_action(self, event):
        x, y = self.get_cell_coordinates(event)
        if not self.out_of_bounds(x, y):
            self.grid.set_pixel(x, y, FILL_COLOUR)
    
    def erase_action(self, event):
        x, y = self.get_cell_coordinates(event)
        if not self.out_of_bounds(x, y):
            self.grid.set_pixel(x, y, BACKGROUND_COLOUR)

    def get_cell_coordinates(self, event):
        return event.x // PIXELS_IN_CELL, event.y // PIXELS_IN_CELL


def main():
    app = MyApplication(16, 16)
    app.start()


if __name__ == "__main__":
    main()
