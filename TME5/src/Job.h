#pragma once
#include <thread>
#include <chrono>
namespace pr {

class Job {
public:
	virtual void run () = 0;
	virtual ~Job() {};
};

// Job concret : exemple

class PixelJob : public Job {
	int calcul (int v) {
		std::cout << "Computing for arg =" << v << std::endl;
		// traiter un gros calcul
		std::this_thread::sleep_for(std::chrono::seconds(1));
		int ret = v % 255;
		std::cout << "Obtained for arg =" << arg <<  " result " << ret << std::endl;
		return ret;
	}
	int arg;
	int * ret;
public :
	PixelJob(Scene scene, int[] screen,int x, int y, int * ret) : ret(ret) {}
	void run () {
			// le point de l'ecran par lequel passe ce rayon
			auto & screenPoint = screen[y][x];
			// le rayon a inspecter
			Rayon  ray(scene.getCameraPos(), screenPoint);

			int targetSphere = findClosestInter(scene, ray);

			if (targetSphere == -1) {
				// keep background color
				return;
			} else {
				const Sphere & obj = *(scene.begin() + targetSphere);
				// pixel prend la couleur de l'objet
				Color finalcolor = computeColor(obj, ray, scene.getCameraPos(), lights);
				// le point de l'image (pixel) dont on vient de calculer la couleur
				Color & pixel = pixels[y*scene.getHeight() + x];
				// mettre a jour la couleur du pixel dans l'image finale.
				pixel = finalcolor;
				* ret = pixel;
				return ret;
			}
	}
	~PixelJob(){}
};
/**
**/

}
