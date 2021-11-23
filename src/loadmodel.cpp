#include<loadmodel.h>
void demo_load_and_save(std::string filepath, voxelRecord& voxel);


loadmodel::loadmodel(const std::string &voxelModelFilepath) {
  filePath = voxelModelFilepath;
  std::string extendName = voxelModelFilepath;
  extendName.erase(0, voxelModelFilepath.find(".", voxelModelFilepath.find("/") ));

  
  if (extendName.compare(".vox") == 0) {
	  std::cout << "File type: " << extendName << std::endl;
	  loadVoxel();
  }

  if (extendName.compare(".obj") == 0) {
	  std::cout << "File type: " << extendName << std::endl;
	  loadObj();
	//  for (int i = 0; i < objModel.size(); i++) {
	//	std::cout << "pos:" << objModel[i].vertexPos.x << " " << objModel[i].vertexPos.y << " " << objModel[i].vertexPos.z <<" "<< objModel[i].vertexPos.w << std::endl;
	//	std::cout << "color:" << objModel[i].vertexColor.x << " " << objModel[i].vertexColor.y << " " << objModel[i].vertexColor.z << " " << objModel[i].vertexColor.w << std::endl;
	//	std::cout << "normal:" << objModel[i].vertexNormal.x << " " << objModel[i].vertexNormal.y << " " << objModel[i].vertexNormal.z << " " << objModel[i].vertexNormal.w << std::endl;
	//}
  }

  
}

loadmodel::loadmodel() {
	modelType = "Vertex";

	// Grid position are in xy clipped space
	std::vector<glm::vec4> gridPlane = {
		glm::vec4(1.0f , 1.0f , 0.0f , 1.0f),
		glm::vec4(-1.0f , -1.0f , 0.0f , 1.0f),
		glm::vec4(-1.0f , 1.0f , 0.0f , 1.0f),
		glm::vec4(1.0f , 1.0f , 0.0f , 1.0f),
		glm::vec4(1.0f , -1.0f , 0.0f , 1.0f),
		glm::vec4(-1.0f , -1.0f , 0.0f , 1.0f)
	};

	vertexData = gridPlane;
	std::cout << "Vertex Load Complete--------------------------------------------------------" << std::endl;
}

loadmodel::~loadmodel() {

}

void loadmodel::genBuffer() {
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);
	
	uint32_t buffer_len;
	if (modelType == "Voxel") {
		buffer_len = modeldata.size() * sizeof(initVoxelData);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, buffer_len, &modeldata[0], GL_STATIC_DRAW);
	}
	if (modelType == "Vertex") {
		buffer_len = vertexData.size() * sizeof(glm::vec4);
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, buffer_len, &vertexData[0], GL_STATIC_DRAW);
	}
	if (modelType == "Obj") {

		buffer_len = objModel.size() * sizeof(vertexBuffer);
		//std::cout << "buffer length: " << objModel.size() << std::endl;
		glBindVertexArray(vao);
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, buffer_len, &objModel[0], GL_STATIC_DRAW);
	}
	//std::cout << modeldata.size() << std::endl;
	//std::cout << indexdata.size() << std::endl;
	
	
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
	std::cout << "x dimension:  " << voxelModel.xDimension << std::endl;
	std::cout << "y dimension:  " << voxelModel.yDimension << std::endl;
	std::cout << "z dimension:  " << voxelModel.zDimension << std::endl;
	std::cout << "total voxels:  " << voxelModel.totalVoxels << std::endl;
};

void loadmodel::genOneVoxeldata(int32_t x, int32_t y, int32_t z, int32_t voxel_index ,vec3 color) {

	if (!(color.x == 0 && color.y == 0 && color.z == 0)) {
		voxelBuffer  tmpData;
		tmpData = initVoxelData;
		for (int i = 0; i < sizeof(initVoxelData) / sizeof(vertexBuffer); i++) {
			tmpData.vexelVertex[i].vertexPos += glm::vec4((float_t)x, (float_t)y, (float_t)z, 0.0f);
			tmpData.vexelVertex[i].vertexColor = glm::vec4((float_t)color.x / 255.0f, (float_t)color.y / 255.0f, (float_t)color.z / 255.0f, 1.0f);
		}
	
		modeldata.push_back(tmpData);

	}
};

glm::mat4 loadmodel::getModelMatrix() {
	return globalRotateMatrix  * localTranslateMatrix  * localRotateMatrix * localScaleMatrix;
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

	rotate = glm::rotate(rotate, glm::radians(x), glm::vec3(1.0f , 0.0f , 0.0f));
	rotate = glm::rotate(rotate, glm::radians(y), glm::vec3(0.0f , 1.0f , 0.0f));
	rotate = glm::rotate(rotate, glm::radians(z), glm::vec3(0.0f , 0.0f , 1.0f));
	
	
	localRotateMatrix = rotate;
};

void loadmodel::globalRotate(float_t x, float_t y, float_t z) {
	glm::mat4 rotate(1.0f);
	glm::vec3 currentRotate(x, y, z);
	glm::vec3 different = currentRotate - oldRotate;

	if ( !((different.x==0.0) && (different.y == 0.0) && (different.z == 0.0)) ) {
		rotate = glm::rotate(rotate, glm::radians(currentRotate.x - oldRotate.x), glm::vec3(1.0f, 0.0f, 0.0f));
		rotate = glm::rotate(rotate, glm::radians(currentRotate.y - oldRotate.y), glm::vec3(0.0f, 1.0f, 0.0f));
		rotate = glm::rotate(rotate, glm::radians(currentRotate.z - oldRotate.z), glm::vec3(0.0f, 0.0f, 1.0f));

		oldRotate = currentRotate;
		globalRotateMatrix = rotate * globalRotateMatrix;
	}
};

uint32_t loadmodel::getVertexNum() {
	
	/*
	one voxel have 36 vertices data
	total voxel*36 is total vertices
	*/
	if(modelType=="Voxel") return modeldata.size() * 36;
	if(modelType=="Vertex") return vertexData.size();
	if(modelType == "Obj") return objModel.size();
}

std::string loadmodel::getModelType() {
	return modelType;
}

void loadmodel::loadVoxel() {
	modelMatrix = glm::mat4(1.0f);
	localTranslateMatrix = glm::mat4(1.0f);
	localRotateMatrix = glm::mat4(1.0f);
	localScaleMatrix = glm::mat4(1.0f);
	globalRotateMatrix = glm::mat4(1.0f);
	oldRotate = glm::vec3(0.0f);

	modelType = "Voxel";
	voxelBuffer  data;
	demo_load_and_save(filePath, voxelModel);
	printVoxelRecord();


	/*
	  glm::vec4 vertexPos
	  glm::vec4 vertexColor
	  glm::vec4 vertexNormal
	  */
	data = {
		//bottom face
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , -1.0f , 0.0f),

		glm::vec4(1.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , -1.0f , 0.0f),

		glm::vec4(1.0f , 1.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , -1.0f , 0.0f),

		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , -1.0f , 0.0f),

		glm::vec4(1.0f , 1.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , -1.0f , 0.0f),

		glm::vec4(0.0f , 1.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , -1.0f , 0.0f),

		//right face
		glm::vec4(1.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(1.0f , 0.0f , 0.0f , 0.0f),

		glm::vec4(1.0f , 1.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(1.0f , 0.0f , 0.0f , 0.0f),

		glm::vec4(1.0f , 1.0f , 1.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(1.0f , 0.0f , 0.0f , 0.0f),

		glm::vec4(1.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(1.0f , 0.0f , 0.0f , 0.0f),

		glm::vec4(1.0f , 1.0f , 1.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(1.0f , 0.0f , 0.0f , 0.0f),

		glm::vec4(1.0f , 0.0f , 1.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(1.0f , 0.0f , 0.0f , 0.0f),

		//back face
		glm::vec4(0.0f , 1.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 1.0f , 0.0f , 0.0f),

		glm::vec4(1.0f , 1.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 1.0f , 0.0f , 0.0f),

		glm::vec4(1.0f , 1.0f , 1.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 1.0f , 0.0f , 0.0f),

		glm::vec4(0.0f , 1.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 1.0f , 0.0f , 0.0f),

		glm::vec4(1.0f , 1.0f , 1.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 1.0f , 0.0f , 0.0f),

		glm::vec4(0.0f , 1.0f , 1.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 1.0f , 0.0f , 0.0f),

		//left face
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(-1.0f , 0.0f , 0.0f , 0.0f),

		glm::vec4(0.0f , 0.0f , 1.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(-1.0f , 0.0f , 0.0f , 0.0f),

		glm::vec4(0.0f , 1.0f , 1.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(-1.0f , 0.0f , 0.0f , 0.0f),

		glm::vec4(0.0f , 1.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(-1.0f , 0.0f , 0.0f , 0.0f),

		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(-1.0f , 0.0f , 0.0f , 0.0f),

		glm::vec4(0.0f , 1.0f , 1.0f , 1.0f),
		glm::vec4(0.0f , 0.0f , 0.0f , 1.0f),
		glm::vec4(-1.0f , 0.0f , 0.0f , 0.0f),

		//front face
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, -1.0f, 0.0f, 0.0f),

		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, -1.0f, 0.0f, 0.0f),

		glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, -1.0f, 0.0f, 0.0f),

		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, -1.0f, 0.0f, 0.0f),

		glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, -1.0f, 0.0f, 0.0f),

		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, -1.0f, 0.0f, 0.0f),

		//top face
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),

		glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),

		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),

		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),

		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),

		glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 0.0f),
	};

	initVoxelData = data;
	int32_t index = 0;

	//go through all voxel coordinate and crate voxel vertices
	for (int32_t z = ceil(-voxelModel.zDimension / 2.0); z < voxelModel.zDimension / 2.0; z++) {

		for (int32_t y = ceil(-voxelModel.yDimension / 2.0); y < voxelModel.yDimension / 2.0; y++) {

			for (int32_t x = ceil(-voxelModel.xDimension / 2.0); x < voxelModel.xDimension / 2.0; x++) {
				vec3 voxelColor = voxelModel.colors[index++];
				genOneVoxeldata(x, y, z, index, voxelColor);

				//std::cout << "( " << x << "," << y << "," << z << ")" << std::endl;
				//std::cout << "( " << voxelColor.x << "," << voxelColor.y << "," << voxelColor.z << ")" << std::endl;
				//std::cout << "--------------------------------------------------------" << std::endl;	  
			}
		}
	}
	std::cout << "Load Complete--------------------------------------------------------" << std::endl;
};
void loadmodel::loadObj() {
	modelType = "Obj";
	std::ifstream objFile(filePath);
	std::string line;

	std::vector<glm::vec3> vertex;
	std::vector<glm::vec3> normal;
	std::vector<vec3> faceRecord;
	glm::vec4 color(0.0f, 0.75f, 0.9f, 1.0f);

	while (getline(objFile, line)) {
		std::string type = line;
		type = type.substr(0,type.find(" "));

		//std::cout << line  <<std::endl;
		
		if (type.compare("v")==0) {
			glm::vec3 v(0.0f);
			line.erase(0, line.find(" ")+1);

			for (int i = 0; i < 3; i++) {

				std::string value = line.substr(0, line.find(" "));
				v[i] = stof(value);
				line.erase(0, line.find(" ")+1);
				
			}
			vertex.push_back(v);
			//std::cout << "vertex:" << v[0] <<" "<< v[1]<<" "<< v[2] << std::endl;
		}
		if (type.compare("vn")==0) {
			glm::vec3 v(0.0f);
			line.erase(0, line.find(" ") + 1);

			for (int i = 0; i < 3; i++) {
				
				std::string value = line.substr(0, line.find(" "));
				v[i] = stof(value);
				line.erase(0, line.find(" ") + 1);
				
			}
			normal.push_back(v);
			//std::cout << "normal:" << v[0] << " " << v[1] << " " << v[2] << std::endl;
		}
		if (type.compare("f") == 0) {
			line.erase(0, line.find(" ") + 1);
			float f[3];

			//each face has three vertices
			for (int i = 0; i < 3; i++) {

				//parse this vertex information
				std::string vertexInfo = line.substr(0, line.find(" "));
					
				for (int j = 0; j < 3; j++) {	
					std::string idx = vertexInfo.substr(0, vertexInfo.find("/"));
					f[j] = stof(idx);
					vertexInfo.erase(0, vertexInfo.find("/") + 1);
				}
					
				faceRecord.push_back({ f[0] ,f[1] ,f[2] });
				line.erase(0, line.find(" ") + 1);
			}
			
			/*for (auto& element : faceRecord) {
				std::cout << "face:" << element.x << " " << element.y << " " << element.z << std::endl;
			}*/
			
		}
		
	}

	glm::vec3* vertexNormalSum = new glm::vec3[vertex.size()];
	for (int i = 0; i < vertex.size(); i++) {
		vertexNormalSum[i] = glm::vec3(0.0f);
	}
	for (auto& element : faceRecord) {
		//find each face per vertex's vertex index and normal index
		int vIndex = element.x-1;
		int nIndex = element.z-1;

		vertexNormalSum[vIndex] += normal[nIndex];
	}
	for (auto& element : faceRecord) {
		//std::cout << faceRecord.size() << std::endl;
		vertexBuffer tmp;
		
		int vIndex = element.x - 1;
		int nIndex = element.z - 1;

		tmp.vertexPos = glm::vec4(vertex[vIndex],1.0f);
		tmp.vertexColor = color;
		//smooth
		tmp.vertexNormal = glm::vec4(glm::normalize(vertexNormalSum[vIndex]) , 0.0f);
		//flat
		//tmp.vertexNormal = glm::vec4(glm::normalize(normal[nIndex]), 0.0f);

		objModel.push_back(tmp);
	}

	//for (int i = 0; i < objModel.size(); i++) {
	//	std::cout << "pos:" << objModel[i].vertexPos.x << " " << objModel[i].vertexPos.y << " " << objModel[i].vertexPos.z << std::endl;
	//	std::cout << "normal:" << objModel[i].vertexNormal.x << " " << objModel[i].vertexNormal.y << " " << objModel[i].vertexNormal.z << std::endl;
	//}

	delete[] vertexNormalSum;
}