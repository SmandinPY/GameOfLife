import random
import time
import os

def create_grid(width, height):
    return [[random.choice([0, 1]) for _ in range(width)] for _ in range(height)]

def print_grid(grid):
    os.system('cls' if os.name == 'nt' else 'clear')  # Clear the terminal
    for row in grid:
        print(''.join(['■' if cell else ' ' for cell in row]))
    print('\n' * 2)  # Add some spacing

def count_neighbors(grid, x, y):
    count = 0
    for dx in [-1, 0, 1]:
        for dy in [-1, 0, 1]:
            if dx == 0 and dy == 0:
                continue
            nx, ny = x + dx, y + dy
            if 0 <= nx < len(grid[0]) and 0 <= ny < len(grid):
                count += grid[ny][nx]
    return count

def evolve(grid):
    new_grid = [[0 for _ in range(len(grid[0]))] for _ in range(len(grid))]
    for y in range(len(grid)):
        for x in range(len(grid[0])):
            neighbors = count_neighbors(grid, x, y)
            if grid[y][x] == 1 and (neighbors < 2 or neighbors > 3):
                new_grid[y][x] = 0
            elif grid[y][x] == 0 and neighbors == 3:
                new_grid[y][x] = 1
            else:
                new_grid[y][x] = grid[y][x]
    return new_grid

def main(width, height, generations, delay):
    grid = create_grid(width, height)
    for _ in range(generations):
        print_grid(grid)
        grid = evolve(grid)
        time.sleep(delay)

if __name__ == "__main__":
    WIDTH = 50
    HEIGHT = 20
    GENERATIONS = 100
    DELAY = 0.1
    main(WIDTH, HEIGHT, GENERATIONS, DELAY)