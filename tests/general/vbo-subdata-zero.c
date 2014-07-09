/*
 * Copyright © 2009 Intel Corporation
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Authors:
 *    Ben Holmes <shranzel@hotmail.com>
 */

#include "piglit-util-gl.h"

PIGLIT_GL_TEST_CONFIG_BEGIN

	config.supports_gl_compat_version = 10;

	config.window_width = 400;
	config.window_height = 300;
	config.window_visual = PIGLIT_GL_VISUAL_RGB | PIGLIT_GL_VISUAL_DOUBLE;

PIGLIT_GL_TEST_CONFIG_END

static GLuint vbo;

void
piglit_init(int argc, char **argv)
{
	piglit_ortho_projection(piglit_width, piglit_height, GL_FALSE);

	piglit_require_extension("GL_ARB_vertex_buffer_object");

	glGenBuffersARB(1, &vbo);
	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo);
	glBufferDataARB(GL_ARRAY_BUFFER_ARB, 12 * sizeof(GLfloat),
			NULL, GL_DYNAMIC_DRAW);
}

static void
vbo_write_floats_mapped(const float *varray, size_t count)
{
	float *ptr = glMapBufferARB(GL_ARRAY_BUFFER_ARB, GL_WRITE_ONLY_ARB);

	if (ptr == NULL)
		piglit_report_result(PIGLIT_FAIL);

	memcpy(ptr, varray, count * sizeof(GLfloat));

	if (!glUnmapBufferARB(GL_ARRAY_BUFFER_ARB))
		piglit_report_result(PIGLIT_FAIL);
}

enum piglit_result
piglit_display(void)
{
	GLfloat white[4] = {1.0, 1.0, 1.0, 0.0};
	GLboolean pass = GL_TRUE;
	GLfloat varray1[12] = {175, 125, 0,
			       175, 175, 0,
			       125, 125, 0,
			       125, 175, 0};
	GLfloat varray2[12] = {275, 125, 0,
			       275, 175, 0,
			       225, 125, 0,
			       225, 175, 0};
	GLenum err;

	glBindBufferARB(GL_ARRAY_BUFFER_ARB, vbo);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	vbo_write_floats_mapped(varray1, 12);

       	glClear(GL_COLOR_BUFFER_BIT);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glBufferSubDataARB(GL_ARRAY_BUFFER_ARB, 0, 0, varray2); /* noop */
	vbo_write_floats_mapped(varray2, 12);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	if ((err = glGetError()) != 0) {
		printf("gl error: 0x%08x\n", err);
		pass = GL_FALSE;
	}

	pass = pass && piglit_probe_pixel_rgb(250, 150, white);
	pass = pass && piglit_probe_pixel_rgb(150, 150, white);

	piglit_present_results();

	glDisableClientState(GL_VERTEX_ARRAY);

	return pass ? PIGLIT_PASS : PIGLIT_FAIL;
}
