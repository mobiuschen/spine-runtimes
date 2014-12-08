/******************************************************************************
 * Spine Runtimes Software License
 * Version 2.1
 * 
 * Copyright (c) 2013, Esoteric Software
 * All rights reserved.
 * 
 * You are granted a perpetual, non-exclusive, non-sublicensable and
 * non-transferable license to install, execute and perform the Spine Runtimes
 * Software (the "Software") solely for internal use. Without the written
 * permission of Esoteric Software (typically granted by licensing Spine), you
 * may not (a) modify, translate, adapt or otherwise create derivative works,
 * improvements of the Software or develop new applications using the Software
 * or (b) remove, delete, alter or obscure any trademarks or any copyright,
 * trademark, patent or other intellectual property or proprietary rights
 * notices on or in the Software, including any copy thereof. Redistributions
 * in binary or source form must include this license and terms.
 * 
 * THIS SOFTWARE IS PROVIDED BY ESOTERIC SOFTWARE "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ESOTERIC SOFTARE BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include <spine/AtlasAttachmentLoader.h>
#include <spine/extension.h>

spAttachment* _spAtlasAttachmentLoader_newAttachment (spAttachmentLoader* loader, spSkin* skin, spAttachmentType type, const char* name, const char* path) {
	switch (type) {
	case SP_ATTACHMENT_REGION: {
		spRegionAttachment* attachment = spRegionAttachment_create(name, path);
		return SUPER(attachment);
	}
	case SP_ATTACHMENT_MESH: {
		spMeshAttachment* attachment = spMeshAttachment_create(name, path);
		return SUPER(attachment);
	}
	case SP_ATTACHMENT_SKINNED_MESH: {
		spSkinnedMeshAttachment* attachment = spSkinnedMeshAttachment_create(name, path);
		return SUPER(attachment);
	}
	case SP_ATTACHMENT_BOUNDING_BOX:
        return SUPER(spBoundingBoxAttachment_create(name));
	default:
		_spAttachmentLoader_setUnknownTypeError(loader, type);
		return 0;
	}
}

int _spAtlasAttachmentLoader_initAttachment (spAttachmentLoader* loader, spAttachment* target) {
    spAtlasAttachmentLoader* self = SUB_CAST(spAtlasAttachmentLoader, loader);
    switch (target->type) {
        case SP_ATTACHMENT_REGION: {
            spRegionAttachment* attachment = SUB_CAST(spRegionAttachment, target);
            if (!attachment->rendererObject) {
                spAtlasRegion* region = spAtlas_findRegion(self->atlas, target->path);
                if (!region) return 0;

                spAtlas_addPageRef(self->atlas, region->page);
                attachment->rendererObject = region;
                spRegionAttachment_setUVs(attachment, region->u, region->v, region->u2, region->v2, region->rotate);
                attachment->regionOffsetX = region->offsetX;
                attachment->regionOffsetY = region->offsetY;
                attachment->regionWidth = region->width;
                attachment->regionHeight = region->height;
                attachment->regionOriginalWidth = region->originalWidth;
                attachment->regionOriginalHeight = region->originalHeight;
            }

            spRegionAttachment_updateOffset(attachment);
            return 1;
        }
        case SP_ATTACHMENT_MESH: {
            spMeshAttachment* attachment = SUB_CAST(spMeshAttachment, target);
            if (!attachment->rendererObject) {
                spAtlasRegion* region = spAtlas_findRegion(self->atlas, target->path);
                if (!region) return 0;

                spAtlas_addPageRef(self->atlas, region->page);
                attachment->rendererObject = region;
                attachment->regionU = region->u;
                attachment->regionV = region->v;
                attachment->regionU2 = region->u2;
                attachment->regionV2 = region->v2;
                attachment->regionRotate = region->rotate;
                attachment->regionOffsetX = region->offsetX;
                attachment->regionOffsetY = region->offsetY;
                attachment->regionWidth = region->width;
                attachment->regionHeight = region->height;
                attachment->regionOriginalWidth = region->originalWidth;
                attachment->regionOriginalHeight = region->originalHeight;
            }

            spMeshAttachment_updateUVs(attachment);
            return 1;
        }
        case SP_ATTACHMENT_SKINNED_MESH: {
            spSkinnedMeshAttachment* attachment = SUB_CAST(spSkinnedMeshAttachment, target);
            if (attachment->rendererObject) {
                spAtlasRegion* region = spAtlas_findRegion(self->atlas, target->path);
                if (!region) return 0;

                spAtlas_addPageRef(self->atlas, region->page);
                attachment->rendererObject = region;
                attachment->regionU = region->u;
                attachment->regionV = region->v;
                attachment->regionU2 = region->u2;
                attachment->regionV2 = region->v2;
                attachment->regionRotate = region->rotate;
                attachment->regionOffsetX = region->offsetX;
                attachment->regionOffsetY = region->offsetY;
                attachment->regionWidth = region->width;
                attachment->regionHeight = region->height;
                attachment->regionOriginalWidth = region->originalWidth;
                attachment->regionOriginalHeight = region->originalHeight;
            }

            spSkinnedMeshAttachment_updateUVs(attachment);
            return 1;
        }
        case SP_ATTACHMENT_BOUNDING_BOX:
            return 1;
        default:
            return 0;
    }
}

int _spAtlasAttachmentLoader_deinitAttachments (spAttachmentLoader* loader, spSkin* skin) {
    spAtlasAttachmentLoader* self = SUB_CAST(spAtlasAttachmentLoader, loader);
    spAttachment** attachments = MALLOC(spAttachment*, skin->attachmentCount);
    int count = spSkin_getAllAttachments(skin, attachments);
    int i;
    for(i = 0; i < count; i++) {
        spAttachment* attachment = attachments[i];
        switch(attachment->type) {
            case SP_ATTACHMENT_REGION: {
                spRegionAttachment* regionAttachment = SUB_CAST(spRegionAttachment, attachment);
                spAtlasRegion* region = regionAttachment->rendererObject;
                if (region) spAtlas_minusPageRef(self->atlas, region->page);
                break;
            }
            case SP_ATTACHMENT_MESH: {
                spMeshAttachment* meshAttachment = SUB_CAST(spMeshAttachment, attachment);
                spAtlasRegion* region = meshAttachment->rendererObject;
                if (region) spAtlas_minusPageRef(self->atlas, region->page);
                break;
            }
            case SP_ATTACHMENT_SKINNED_MESH: {
                spSkinnedMeshAttachment* skinnedMeshAttachment = SUB_CAST(spSkinnedMeshAttachment, attachment);
                spAtlasRegion* region = skinnedMeshAttachment->rendererObject;
                if (region) spAtlas_minusPageRef(self->atlas, region->page);
                break;
            }
            case SP_ATTACHMENT_BOUNDING_BOX:
                break;
            default:
                _spAttachmentLoader_setUnknownTypeError(loader, attachment->type);
				FREE(attachments);
                return 0;
        }//switch
    }//for
	FREE(attachments);
    return 1;
}

spAtlasAttachmentLoader* spAtlasAttachmentLoader_create (spAtlas* atlas) {
	spAtlasAttachmentLoader* self = NEW(spAtlasAttachmentLoader);
	_spAttachmentLoader_init(
            SUPER(self),
            _spAttachmentLoader_deinit,
            _spAtlasAttachmentLoader_newAttachment,
            _spAtlasAttachmentLoader_initAttachment,
            _spAtlasAttachmentLoader_deinitAttachments
    );
	self->atlas = atlas;
	return self;
}
