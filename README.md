# RTV1

My first ray-tracer
____

Requirements for this project were:
- Implementing ray tracing method to generate computer images.
- Use parametric equations to determine ray intersections with spheres, planes, cylinders and cones.
- Be able to modify object position, direction/rotation, and size.
- Use Lambertian method(diffuse shading)
- Use Phong-Blinn method (specular lighting)
- Handle shadows.
- Handle muliple colored lights.
- Have a file that defines objects, lights and the camera(s) which is parsed at the beginning of the program.
____

## Compile

	make
____

## Run

	./rtv1 scenes/scene7.rt
____

Here is a simple file parsed by my program: 

	// Comments starts with '//'
	CAM {position: (0, 0, -2000), direction: (0, 0, 1);
	MAT {diffusion: (255, 0, 0), reflexion: 0, specvalue: 100, specpower: 100};
	MAT {diffusion: (0, 255, 0), reflexion: 0, specvalue: 100, specpower: 100};
	MAT {diffusion: (0, 0, 255), reflexion: 0, specvalue: 100, specpower: 100};
	LIGHT {position: (2000, 0, -1000), intensity: (255, 255, 255)};
	LIGHT {position: (2000, 0, -1000), intensity: (0, 128, 0)} +T (-4000, 0, 0);
	SPHERE {center: (900, 500, 200), radius: 250, mat: 2};
	SPHERE {center: (900, 500, 200), radius: 250, mat: 2} +T (-1800, 0, 0);
	SPHERE {center: (900, 500, 200), radius: 250, mat: 2} +T (0, 0, 700);
	SPHERE {center: (900, 500, 200), radius: 250, mat: 2} +T (-1800, 0, 700);
	SPHERE {center: (900, 500, 200), radius: 250, mat: 2} +T (0, -1000, 0);
	SPHERE {center: (900, 500, 200), radius: 250, mat: 2} +T (-1800, -1000, 0);
	SPHERE {center: (900, 500, 200), radius: 250, mat: 2} +T (0, -1000, 700);
	SPHERE {center: (900, 500, 200), radius: 250, mat: 2} +T (-1800, -1000, 700);
	SPHERE {center: (0, 0, 0), radius: 100, mat: 0};
	CYLINDER {direction: (0, 1, 0), axispoint: (900, 0, 200), radius: 150, mat: 2};
	CYLINDER {direction: (0, 1, 0), axispoint: (900, 0, 200), radius: 150, mat: 2} +T (-1800, 0, 0);
	CYLINDER {direction: (0, 1, 0), axispoint: (900, 0, 200), radius: 150, mat: 2} +T (0, 0, 700);
	CYLINDER {direction: (0, 1, 0), axispoint: (900, 0, 200), radius: 150, mat: 2} +T (-1800, 0, 700);
	PLANE {normale: (0, 1, 0), d: -500, mat: 1} +T (0, -1000, 0);
	PLANE {normale: (0, 1, 0), d: -500, mat: 1} +T (0, 1000, 0) +R (90, 0, 0);
	PLANE {normale: (0, 0, 1), d: -1500, mat: 1};
	PLANE {normale: (0, 1, 0), d: -500, mat: 1};
____

## Screenshots

Here is the output of the file above:
![Rendu 1](https://github.com/squiquem/RTV1/blob/master/screenshots/scene7.PNG)

Enjoy another cool picture!
![Rendu 2](https://github.com/squiquem/RTV1/blob/master/screenshots/scene9.PNG)
____

If you have any questions or suggestions, feel free to send me an email at squiquem@student.42.fr
