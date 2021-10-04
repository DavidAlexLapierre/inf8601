#include <stdio.h>

#include "filter.h"
#include "pipeline.h"
#include "tbb/pipeline.h"

extern "C" {
    image_dir_t* directory;

    class Load {
        public:
            image_t* operator()(tbb::flow_control& fc) const {
                image_t* img = image_dir_load_next(directory);

                if (img == NULL)
                    fc.stop();

                return img;
            }
    };

    class Scale {
        public:
            image_t* operator()(image_t* image) const {
                image_t* image_scale = filter_scale_up(image,2);
                return image_scale;
            }
    };

    class Desaturate {
        public:
            image_t* operator()(image_t* image) const {
                image_t* image_desaturate = filter_desaturate(image);
                return image_desaturate;
            }
    };

    class Flip {
        public:
            image_t* operator()(image_t* image) const {
                image_t* image_flip = filter_horizontal_flip(image);
                return image_flip;
            }
    };

    class Sobel {
        public:
            image_t* operator()(image_t* image) const {
                image_t* image_flip = filter_sobel(image);
                return image_flip;
            }
    };

    class Save {
        public:
            void operator()(image_t* image) const {
                image_dir_save(directory, image);

                printf(".");
                fflush(stdout);

                image_destroy(image);    
            }
        };

    void RunPipeline(int ntoken) {
        tbb::parallel_pipeline(
            ntoken,
            tbb::make_filter<void,image_t*>(
                tbb::filter::serial_in_order, Load())
        &
            tbb::make_filter<image_t*,image_t*>(
                tbb::filter::serial_out_of_order, Scale() )
        &
            tbb::make_filter<image_t*,image_t*>(
                tbb::filter::serial_out_of_order, Desaturate() )
        &
            tbb::make_filter<image_t*,image_t*>(
                tbb::filter::serial_out_of_order, Flip() )
        &
            tbb::make_filter<image_t*,image_t*>(
                tbb::filter::serial_out_of_order, Sobel() )
        &
            tbb::make_filter<image_t*,void>(
                tbb::filter::serial_in_order, Save()));
    }

    int pipeline_tbb(image_dir_t* image_dir) {
        directory = image_dir;

        RunPipeline(6);
        
        return -1;
    }
} /* extern "C" */
