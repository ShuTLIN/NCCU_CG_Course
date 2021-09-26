#include<loadmodel.h>
void demo_load_and_save(std::string filepath, voxel_record& voxel);


loadmodel::loadmodel(const std::string &voxelModelFilepath) {
  modelMatrix = glm::mat4(1.0f);
  databuffer  data;
  demo_load_and_save(voxelModelFilepath, voxel_model);
  printVoxelRecord();

  //initialize first voxel index buffer
  std::vector<uint32_t> firstVoxelIndexs = std::vector<uint32_t>({
	0,1,3,0,3,2,
	0,1,5,0,5,4,
	1,3,7,1,7,5,
	0,4,6,2,0,6,
	2,3,7,2,7,6,
	4,5,7,4,7,6
	  });
  indexdata = firstVoxelIndexs;

  int32_t index = 0;
  //walk through all vexel coordinate
  for (int32_t z = ceil(-voxel_model.z_dimension/2.0) ; z < voxel_model.z_dimension / 2.0; z++) {

	  for (int32_t y = ceil(-voxel_model.y_dimension / 2.0); y < voxel_model.y_dimension / 2.0; y++) {

		  for (int32_t x = ceil(-voxel_model.x_dimension / 2.0); x < voxel_model.x_dimension / 2.0; x++) {
			  vec3 voxelColor = voxel_model.colors[index++];
			  genOneVoxeldata(x , y, z , index ,voxelColor);

			  //std::cout << "( " << x << "," << y << "," << z << ")" << std::endl;
			  //std::cout << "( " << voxelColor.x << "," << voxelColor.y << "," << voxelColor.z << ")" << std::endl;
			  //std::cout << "--------------------------------------------------------" << std::endl;	  
		  }
	  }
  }
  std::cout << "Load Complete--------------------------------------------------------" << std::endl;
}

loadmodel::~loadmodel() {

}

void loadmodel::genBuffer() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	glGenBuffers(1, &ibo);
	
	uint32_t buffer_len = modeldata.size() * sizeof(databuffer);
	uint32_t index_buffer_len = indexdata.size() * sizeof(uint32_t);
	
	//std::cout << indexdata.size() << std::endl;
	
	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, buffer_len, &modeldata[0] , GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), BUFFER_OFFSET(4*sizeof(float)));
	

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_len, &indexdata[0] , GL_STATIC_DRAW);

}

void loadmodel::bindVao() {
	glBindVertexArray(vao);
}

uint32_t loadmodel::getVao() {
	return vao;
}

uint32_t loadmodel::getIbo() {
	return ibo;
}

uint32_t loadmodel::getBufferLen() {
	return modeldata.size();
}

uint32_t loadmodel::getIndexLen() {
	return indexdata.size();
}

void loadmodel::printVoxelRecord() {
	std::cout << "x dimension:  " << voxel_model.x_dimension << std::endl;
	std::cout << "y dimension:  " << voxel_model.y_dimension << std::endl;
	std::cout << "z dimension:  " << voxel_model.z_dimension << std::endl;
	std::cout << "total voxels:  " << voxel_model.total_voxels << std::endl;
};

void loadmodel::genOneVoxeldata(int32_t x, int32_t y, int32_t z, int32_t voxel_index ,vec3 color) {
	for (int32_t z_offset = 0; z_offset < 2; z_offset++) {
		for (int32_t y_offset = 0; y_offset < 2; y_offset++) {
			for (int32_t x_offset = 0; x_offset < 2; x_offset++) {

				//std::cout << (float_t)x + (float_t)x_offset << " " << (float_t)y + (float_t)y_offset << " " << " " << (float_t)z + (float_t)z_offset << std::endl;
		
				if ( !(color.x == 0 && color.y == 0 && color.z == 0) ) {
					databuffer  data;
					data.vertexPos = glm::vec4((float_t)x + (float_t)x_offset, (float_t)y + (float_t)y_offset, (float_t)z + (float_t)z_offset, 1.0f);
					data.vertexColor = glm::vec4((float_t)color.x / 255.0f, (float_t)color.y / 255.0f, (float_t)color.z / 255.0f, 1.0f);
					modeldata.push_back(data);
				}			
			}
		}
	}

	if (voxel_index > 0) {
		for (int32_t index = 0; index < 36; index++) {
			uint32_t new_index = indexdata[index] + (uint32_t)8 * (uint32_t)voxel_index;
			indexdata.push_back(new_index);
		}
	}
};

glm::mat4 loadmodel::getModelMatrix() {
	return globalRotateMatrix  * localTranslateMatrix * localScaleMatrix * localRotateMatrix;
};

void loadmodel::localTranslate(float_t x, float_t y, float_t z) {
	glm::mat4 trans(1.0f);
	trans[3]=glm::vec4(x,y,z,1.0f);
	localTranslateMatrix = trans;
};


void loadmodel::localScale(float_t x, float_t y, float_t z) {
	glm::mat4 scale(1.0f);
	scale[0][0] = x;
	scale[1][1] = y;
	scale[2][2] = z;
	localScaleMatrix = scale;
};

void loadmodel::localRotate(float_t x, float_t y, float_t z) {
	glm::mat4 rotate(1.0f);
	rotate = glm::rotate(rotate , glm::radians(x), glm::vec3(1.0f , 0.0f , 0.0f));
	rotate = glm::rotate(rotate , glm::radians(y), glm::vec3(0.0f , 1.0f , 0.0f));
	rotate = glm::rotate(rotate , glm::radians(z), glm::vec3(0.0f , 0.0f , 1.0f));
	localRotateMatrix = rotate;
};

void loadmodel::globalRotate(float_t x, float_t y, float_t z) {
	glm::mat4 rotate(1.0f);
	rotate = glm::rotate(rotate, glm::radians(x), glm::vec3(1.0f, 0.0f, 0.0f));
	rotate = glm::rotate(rotate, glm::radians(y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotate = glm::rotate(rotate, glm::radians(z), glm::vec3(0.0f, 0.0f, 1.0f));
	globalRotateMatrix = rotate;
};
