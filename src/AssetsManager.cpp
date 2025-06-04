
#include <AssetsManager.h>
#include <string>
#include <iostream>


/* ---------------- GENERATING WORLD HELPER FUNC ---------------- */
void	generateRandomBlocksModel(AssetsManager* assetsManager) {
	for (int i = 0; i < 4; i++) {
		float width = 1 + (5 - 1) * ((double)rand() / (double(RAND_MAX) + 1));
		float height = 1 + (5 - 1) * ((double)rand() / (double(RAND_MAX) + 1));
		float length = 1 + (5 - 1) * ((double)rand() / (double(RAND_MAX) + 1));
		
		assetsManager->models[std::string("BLOCK_") + std::to_string(i)] = LoadModelFromMesh(GenMeshCube(width, height, length));
	}
}


AssetsManager::AssetsManager() {
	// loads models
	models["GROUND"] = LoadModelFromMesh(GenMeshCube(100, 1, 100));
	generateRandomBlocksModel(this);
	models["BULLET"] = LoadModelFromMesh(GenMeshCube(0.1f, 0.1f, 0.1f));

	for (std::map<std::string, Model>::iterator i = models.begin(); i != models.end(); i++) {
		std::cout << "INFO: Loaded model: " << i->first << std::endl;
	}
}

AssetsManager::~AssetsManager() {
	// unloads models
	for (std::map<std::string, Model>::iterator i = models.begin(); i != models.end(); i++) {
		UnloadModel(i->second);
	}
}
