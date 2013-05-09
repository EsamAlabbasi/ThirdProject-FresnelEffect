//
//  NormalShaderNode.h
//  Ders 7
//
//  Created by Gurel Erceis on 4/1/13.
//  Copyright (c) 2013 Yogurt3D. All rights reserved.
//

#ifndef NormalShaderNode_h
#define NormalShaderNode_h
#include <windows.h>
#include "Camera.h"
#include "ShadedGeometry.h"

class NormalShaderNode: public ShadedGeometry{
public:
	GLint varyingLocation0;
	GLint varyingLocation1;

	NormalShaderNode(char *filename):
		ShadedGeometry(filename,
		"normal_vert_shader.vert",
		"normal_frag_shader.frag")
	{
		generateBuffers();
		varyingLocation0 = .2f;
		varyingLocation1 = 1.0f;
	}

	~NormalShaderNode(){}

	void draw(SceneNode *camera){

		glUseProgram(programId);

		glm::mat4 MVPmatrix = ((Camera*)camera)->projectionMatrix * camera->getInverseModelMatrix() * getModelMatrix();
		glm::mat4 MVmatrix = camera->getInverseModelMatrix() * getModelMatrix();

		glUniformMatrix4fv(UniformMVP, 1, GL_FALSE, &MVPmatrix[0][0]);

		glUniform1f(Location0, varyingLocation0);
		glUniform1f(Location1, varyingLocation1);	

		// vertex bufferi bagla
		glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
		glVertexAttribPointer(AttributePosition, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// normal buffer i bagla
		glBindBuffer(GL_ARRAY_BUFFER, normalBufferID);
		glVertexAttribPointer(AttributeNormal, 3, GL_FLOAT, GL_FALSE, 0, BUFFER_OFFSET(0));
		glBindBuffer(GL_ARRAY_BUFFER, 0);

		// indiceleri bagla
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indiceBufferID);

		// Attributelari enable et
		glEnableVertexAttribArray(AttributePosition);
		glEnableVertexAttribArray(AttributeNormal);

		// ciz
		glDrawElements(GL_TRIANGLES, int(faceArray.size()), GL_UNSIGNED_INT, BUFFER_OFFSET(0));

		// baglantilari kopar
		glDisableVertexAttribArray(AttributeNormal);
		glDisableVertexAttribArray(AttributePosition);
		glBindBuffer(GL_ARRAY_BUFFER,0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);

		glUseProgram(0);
	}
protected:
	GLint Location0;
	GLint Location1;
private:
	GLuint UniformMVP;
	GLuint AttributePosition,AttributeNormal;

	void generateBuffers(){

		UniformMVP = glGetUniformLocation(programId, "MVP");
		printf("UniformMVP: %d\n",UniformMVP);


		AttributePosition = glGetAttribLocation(programId, "Position");
		printf("Position Attribute: %d\n", AttributePosition);

		AttributeNormal = glGetAttribLocation(programId, "Normal");
		printf("Normal Attribute: %d\n", AttributeNormal);

		Location0 = glGetUniformLocation(programId, "R0");
		Location1 = glGetUniformLocation(programId, "R1");

		if (Location0 == -1)
			std::cout << "Error for R0\n";

		if (Location1 == -1)
			std::cout << "Error for R1!\n";
	}
};

#endif