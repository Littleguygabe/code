import numpy as np
import os
import time
from math import cos, sin, radians

def draw_line(canvas, x0, y0, x1, y1, char='#'):
    x0, y0, x1, y1 = int(x0), int(y0), int(x1), int(y1)

    dx = abs(x1 - x0)
    dy = abs(y1 - y0)
    sx = 1 if x0 < x1 else -1
    sy = 1 if y0 < y1 else -1
    err = dx - dy

    while True:
        if 0 <= y0 < canvas.shape[0] and 0 <= x0 < canvas.shape[1]:
            canvas[y0, x0] = char
        
        if x0 == x1 and y0 == y1:
            break
        
        e2 = 2 * err
        if e2 > -dy:
            err -= dy
            x0 += sx
        if e2 < dx:
            err += dx
            y0 += sy

def draw_square(canvas, vertices, angle_radians, center_x, center_y, scale):
    canvas.fill(' ') 

    rotation_matrix = np.array([
        [cos(angle_radians), -sin(angle_radians)],
        [sin(angle_radians), cos(angle_radians)]
    ])

    screen_coords = []
    for i in range(vertices.shape[0]):
        vertex = vertices[i]

        rotated_vertex = np.dot(rotation_matrix, vertex.reshape((2,1)))

        rotated_x = rotated_vertex[0, 0]
        rotated_y = rotated_vertex[1, 0]

        screen_x = int(rotated_x * scale + center_x)
        screen_y = int(rotated_y * scale + center_y)
        
        screen_coords.append((screen_x, screen_y))

    for i in range(len(screen_coords)):
        p1 = screen_coords[i]
        p2 = screen_coords[(i + 1) % len(screen_coords)]
        draw_line(canvas, p1[0], p1[1], p2[0], p2[1], '#')

    os.system('clear')
    for row in canvas:
        print("".join(row))

def main():
    print('Initializing square rotation animation...')


    rows, cols = 20, 40 
    tdSpace = np.full((rows, cols), ' ')

    square_vertices = np.array([
        [-1,  1],
        [ 1,  1],
        [ 1, -1],
        [-1, -1]
    ], dtype=float)

    center_x = cols // 2
    center_y = rows // 2

    scale = 6

    angle_degrees = 0

    while True:
        angle_radians = radians(angle_degrees)
        
        draw_square(tdSpace, square_vertices, angle_radians, center_x, center_y, scale)

        angle_degrees += 5
        
        if angle_degrees >= 360:
            angle_degrees -= 360
        time.sleep(0.1)

if __name__ == "__main__":
    main()
