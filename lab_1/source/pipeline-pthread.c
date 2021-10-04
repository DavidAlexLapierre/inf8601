#include <stdio.h>

#include "filter.h"
#include "pipeline.h"
#include "pthread.h"
#include <unistd.h>
#include <queue.h>

queue_t* q_double;
queue_t* q_desat;
queue_t* q_flip;
queue_t* q_sob;
queue_t* q_save;

void load_image(image_dir_t* image_dir) {
    image_t* image = image_dir_load_next(image_dir);
    queue_push(q_double, image);
}

void double_image() {
    image_t* img = queue_pop(q_double);
    img = filter_scale_up(img, 2);
    queue_push(q_desat, img);
}

void desaturate_image() {
    image_t* img = queue_pop(q_desat);
    img = filter_desaturate(img);
    queue_push(q_flip, img);
}

void flip_image() {
    image_t* img = queue_pop(q_flip);
    img = filter_horizontal_flip(img);
    queue_push(q_sob, img);
}

void sobel_filter() {
    image_t* img = queue_pop(q_sob);
    img = filter_sobel(img);
    queue_push(q_save, img);
}

void save_image(image_dir_t* image_dir) {
    image_t* img = queue_pop(q_save);
    image_dir_save(image_dir, img);
    image_destroy(img);
}

int pipeline_pthread(image_dir_t* image_dir) {
    q_double = queue_create(10);
    q_desat = queue_create(10);
    q_flip = queue_create(10);
    q_sob = queue_create(10);
    q_save = queue_create(10);

    pthread_t load_id;
    pthread_t double_id;
    pthread_t desat_id;
    pthread_t flip_id;
    pthread_t sobel_id;
    pthread_t save_id;

    while (1) {
        // Load
        pthread_create(&load_id, NULL, (void*) &load_image, image_dir);
        if (q_double->size > 0) pthread_create(&double_id, NULL, (void*) &double_image, NULL);
        if (q_desat->size > 0) pthread_create(&desat_id, NULL, (void*) &desaturate_image, NULL);
        if (q_flip->size > 0) pthread_create(&flip_id, NULL, (void*) &flip_image, NULL);
        if (q_sob->size > 0) pthread_create(&sobel_id, NULL, (void*) &sobel_filter, NULL);
        if (q_save->size > 0) pthread_create(&save_id, NULL, (void*) &save_image, image_dir);

        printf(".");
        fflush(stdout);

        if (q_save->size == 0 && q_save->size == 0) break;

    }

    queue_destroy(q_double);
    queue_destroy(q_desat);
    queue_destroy(q_flip);
    queue_destroy(q_sob);
    queue_destroy(q_save);

    return 0;
}   