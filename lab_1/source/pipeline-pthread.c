#include <stdio.h>

#include "filter.h"
#include "pipeline.h"
#include "pthread.h"
#include <unistd.h>
#include <queue.h>

int mod_img = 0;
int nb_img = 0;

pthread_mutex_t mutex;

queue_t* q_double;
queue_t* q_desat;
queue_t* q_flip;
queue_t* q_sob;
queue_t* q_save;

void load_image(image_dir_t* image_dir) {
    pthread_mutex_lock(&mutex);
    image_t* img = image_dir_load_next(image_dir);
    if (img != NULL) { queue_push(q_double, img); ++nb_img; ++mod_img; }
    pthread_mutex_unlock(&mutex);
}

void double_image() {
    image_t* img = queue_pop(q_double);
    if (img != NULL) {
        img = filter_scale_up(img, 2);
        queue_push(q_desat, img);
    }
}

void desaturate_image() {
    image_t* img = queue_pop(q_desat);
    if (img != NULL) {
        img = filter_desaturate(img);
        queue_push(q_flip, img);
    }
}

void flip_image() {
    image_t* img = queue_pop(q_flip);
    if (img != NULL) {
        img = filter_horizontal_flip(img);
        queue_push(q_sob, img);
    }
}

void sobel_filter() {
    image_t* img = queue_pop(q_sob);
    if (img != NULL) {
        img = filter_sobel(img);
        queue_push(q_save, img);
    }
}

void save_image(image_dir_t* image_dir) {
    image_t* img = queue_pop(q_save);
    if (img != NULL) {
        image_dir_save(image_dir, img);
        //image_destroy(img);
        printf(".");
        fflush(stdout);
        --mod_img;
    }
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

    load_image(image_dir);

    while (mod_img > 0) {
        // Load
        pthread_create(&load_id, NULL, (void*) &load_image, image_dir);
        pthread_create(&double_id, NULL, (void*) &double_image, NULL);
        pthread_create(&desat_id, NULL, (void*) &desaturate_image, NULL);
        pthread_create(&flip_id, NULL, (void*) &flip_image, NULL);
        pthread_create(&sobel_id, NULL, (void*) &sobel_filter, NULL);
        pthread_create(&save_id, NULL, (void*) &save_image, image_dir);
    }

    return 0;
}   