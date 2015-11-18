#!/usr/bin/python

import copy
import itertools
import os
import sys

MAX_SIZE = None

EMPTY = " "
FULL = "X"

TWO_PIECE = [
    [[FULL]*4],
    [[FULL]*3,
     [EMPTY]*2 + [FULL], ],
    [[FULL]*2,
     [FULL]*2],
    [[FULL],
     [FULL],
     [FULL]*2, ],
    [[FULL]*2,
     [EMPTY] + [FULL]*2],
    [[FULL],
     [FULL]*2,
     [EMPTY] + [FULL]],
]


def create_homogenous_shape(elem, size):
    return [[elem for _ in range(size)] for _ in range(size)]


def pad_to_size(shape, size):
    padded = create_homogenous_shape(EMPTY, size)
    for row_index, row in enumerate(shape):
        for column_index, elem in enumerate(row):
            padded[row_index][column_index] = elem

    return padded


def shape_to_string(shape):
    shape_string = os.linesep.join(["".join([str(elem) for elem in row])
                                    for row in shape])
    return shape_string


def is_valid_coordinate(coordinate):
    row, column = coordinate
    return row >= 0 and column >= 0 and row < MAX_SIZE and column < MAX_SIZE


def neighbours(coordinate):
    row, column = coordinate
    possible_neighbours = [(row + 1, column), (row, column + 1),
                           (row - 1, column), (row, column - 1), ]
    return [coordinate for coordinate in possible_neighbours
            if is_valid_coordinate(coordinate)]


def empty_neighbours(coordinate, shape):
    return [(r, c) for (r, c) in neighbours(coordinate)
            if shape[r][c] == EMPTY]


def has_full_neighbour(coordinate, shape):
    full_neighbours = [(r, c) for (r, c) in neighbours(coordinate)
                       if shape[r][c] == FULL]

    return full_neighbours != []


def find_free_places(shape):
    free_places = []
    for row_index, row in enumerate(shape):
        for column_index, elem in enumerate(row):
            if elem == EMPTY and \
               has_full_neighbour((row_index, column_index), shape):
                good_neighbours = empty_neighbours((row_index, column_index),
                                                   shape)
                free_places += [((row_index, column_index), coordinate)
                                for coordinate in good_neighbours]

    return free_places


def fill_places(place1, place2, shape):
    shape_copy = copy.deepcopy(shape)
    row1, column1 = place1
    row2, column2 = place2
    shape_copy[row1][column1] = FULL
    shape_copy[row2][column2] = FULL

    return shape_copy


def get_empty_places(shape):
    empty_places = []
    for row_index, row in enumerate(shape):
        for column_index, elem in enumerate(row):
            if elem == EMPTY:
                empty_places.append((row_index, column_index))

    return empty_places


def flood(coordinate, shape):
    row_index, column_index = coordinate
    shape[row_index][column_index] = FULL
    for neighbour in empty_neighbours(coordinate, shape):
        flood(neighbour, shape)


def fill_up(shape):
    last = (MAX_SIZE - 1, MAX_SIZE - 1)
    shape_copy = copy.deepcopy(shape)
    flood(last, shape_copy)
    return shape_copy


def has_hole(shape):
    full = create_homogenous_shape(FULL, MAX_SIZE)
    filled_up = fill_up(shape)
    if filled_up == full:
        return False

    return True


def move_to_start(shape):
    last_row_index = MAX_SIZE
    for row_index, row in enumerate(shape):
        if row == [EMPTY]*MAX_SIZE:
            last_row_index = row_index
            break
    bottom_cropped = shape[:last_row_index]
    column_indexes = [0]*len(bottom_cropped)
    for row_index, row in enumerate(bottom_cropped):
        column_indexes[row_index] = row.index(FULL)

    first_column_index = min(column_indexes)

    return [row[first_column_index:] for row in bottom_cropped]


def rotate_right(shape):
    new_shape = create_homogenous_shape(EMPTY, MAX_SIZE)
    for row_index, row in enumerate(shape):
        for column_index, elem in enumerate(row):
            new_shape[row_index][column_index] = \
                    shape[MAX_SIZE - column_index - 1][row_index]

    return pad_to_size(move_to_start(new_shape), MAX_SIZE)


def add_brick(shape, result):
    new_shapes = []
    free_places = find_free_places(shape)
    for place1, place2 in free_places:
        filled_shape = fill_places(place1, place2, shape)
        right = rotate_right(filled_shape)
        upside_down = rotate_right(right)
        left = rotate_right(upside_down)
        if not has_hole(filled_shape) and \
           filled_shape not in (result + new_shapes) and \
           right not in (result + new_shapes) and \
           upside_down not in (result + new_shapes) and \
           left not in (result + new_shapes):
            new_shapes.append(filled_shape)

    return new_shapes


def add_one_more_brick(shapes):
    new_shapes = []
    for shape in shapes:
        padded_shape = pad_to_size(shape, MAX_SIZE)
        new_shapes += add_brick(padded_shape, new_shapes)

    return new_shapes


def create_shapes(brick_number):
    if brick_number < 2:
        raise ValueError("Brick number must be at least 2")

    shapes = TWO_PIECE
    for i in range(2, brick_number):
        shapes = add_one_more_brick(shapes)
        print("{} piece done".format(i+1))

    return shapes


def write_shapes_to_file(shapes, brick_number):
    file_name = "tetris-{}.txt".format(brick_number)
    shape_number = len(shapes)
    with open(file_name, 'w') as handler:
        handler.write("{} {}{}".format(shape_number, MAX_SIZE, os.linesep))
        for shape in shapes:
            handler.write(shape_to_string(shape))
            handler.write(os.linesep)


if __name__ == '__main__':
    try:
        number_of_bricks = int(sys.argv[1])
    except:
        print("Exactly one integer argument required")
        sys.exit(1)

    MAX_SIZE = number_of_bricks*2
    shapes = create_shapes(number_of_bricks)
    write_shapes_to_file(shapes, number_of_bricks)
    print("Number of shapes generated to file: {}".format(len(shapes)))
