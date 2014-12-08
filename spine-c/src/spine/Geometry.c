//
//  Geometry.c
//
//  Created by mobiuschen on 10/11/14.
//
//

#include "Geometry.h"
#include "extension.h"
#include <math.h>

spRect* spRect_create(float x, float y, float width, float height) {
    spRect* ret = NEW(spRect);
    ret->x = x;
    ret->y = y;
    ret->width = width;
    ret->height = height;

    return ret;
}

void spRect_dispose(spRect* self) {
    FREE(self);
}

void spRect_merge(spRect *rect1, const spRect *rect2) {
    float top1    = rect1->y + rect1->height;
    float left1   = rect1->x;
    float right1  = rect1->x + rect1->width;
    float bottom1 = rect1->y;

    float top2    = rect2->y + rect2->height;
    float left2   = rect2->x;
    float right2  = rect2->x + rect2->width;
    float bottom2 = rect2->y;


    rect1->x = left1 < left2 ? left1 : left2;
    rect1->y = bottom1 < bottom2 ? bottom1 : bottom2;
    rect1->width = (right1 > right2 ? right2 : right2) - rect1->x;
    rect1->height = (top1 > top2 ? top1 : top2) - rect1->y;
}




spTransform* spTransform_create(float x, float y, float rotation, float scaleX, float scaleY) {
    spTransform* self = NEW(spTransform);
    spTransform_set_values(self, x, y, rotation, scaleX, scaleY);
    return self;
}

spTransform* spTransform_create_default() {
    return spTransform_create(0, 0, 0, 1, 1);
}


void spTransform_dispose(spTransform* self)
{
    FREE(self);
}

void spTransform_set_values(spTransform* self, float x, float y, float rotation, float scaleX, float scaleY)
{
    self->x = x;
    self->y = y;
    self->rotation = rotation;
    self->scaleX = scaleX;
    self->scaleY = scaleY;
}

void spTransform_copy(spTransform* target, const spTransform* src) {
    target->x = src->x;
    target->y = src->y;
    target->scaleX = src->scaleX;
    target->scaleY = src->scaleY;
    target->rotation = src->rotation;
}