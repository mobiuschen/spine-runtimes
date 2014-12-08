//
//  Geometry.h
//
//  Created by mobiuschen on 10/11/14.
//
//

#ifndef SPINE_GEOMERY_H_
#define SPINE_GEOMERY_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif


typedef struct spRect spRect;
typedef struct spTransform spTransform;

struct spRect {
    float x, y;
    float width, height;
};

void spRect_merge(spRect *rect1, const spRect *rect2);


struct spTransform {
    float x, y;
    float rotation;
    float scaleX, scaleY;
};


spTransform* spTransform_create(float x, float y, float rotation, float scaleX, float scaleY);
spTransform* spTransform_create_default();
void spTransform_dispose(spTransform* self);

void spTransform_set_values(spTransform* self, float x, float y, float rotation, float scaleX, float scaleY);
void spTransform_copy(spTransform* target, const spTransform* src);

#ifdef __cplusplus
}
#endif

#endif /* defined(SPINE_GEOMERY_H_) */
