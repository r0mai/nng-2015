#!/usr/bin/python

import copy
import os

MAX_SIZE = 8

EMPTY = 0
FULL = 1

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


def pretty_print_shape(shape):
    shape_string = os.linesep.join(["".join([str(elem) for elem in row])
                                    for row in shape])
    print(shape_string)


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
            if shape[r][c] == 0]


def has_full_neighbour(coordinate, shape):
    full_neighbours = [(r, c) for (r, c) in neighbours(coordinate)
                       if shape[r][c] == FULL]

    return full_neighbours != []


def find_free_places(shape):
    free_places = []
    for row_index, row in enumerate(shape):
        for column_index, elem in enumerate(row):
            if elem == 0 and \
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
            if elem == 0:
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


def add_brick(shape, result):
    new_shapes = []
    free_places = find_free_places(shape)
    for place1, place2 in free_places:
        filled_shape = fill_places(place1, place2, shape)
        if not has_hole(filled_shape) and filled_shape not in result:
            new_shapes.append(filled_shape)

    return new_shapes

if __name__ == '__main__':
    shapes_3 = []
    for two_piece_shape in TWO_PIECE:
        padded_shape = pad_to_size(two_piece_shape, MAX_SIZE)
        shapes_3 += add_brick(padded_shape, shapes_3)

    shapes_4 = []
    for three_piece_shape in shapes_3:
        shapes_4 += add_brick(three_piece_shape, shapes_4)

    for four_piece_shape_shape in shapes_4:
        pretty_print_shape(four_piece_shape_shape)
        print(os.linesep)
    print(len(shapes_3))
    print(len(shapes_4))
