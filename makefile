program: program.o glad.o resourceManager.o shader.o texture.o game.o spriteRenderer.o gameObject.o  ballObject.o Particle_gen.o textRenderer.o
	g++ -o program.exe program.o glad.o resourceManager.o shader.o texture.o game.o spriteRenderer.o gameObject.o ballObject.o  Particle_gen.o textRenderer.o -L ./lib -lfreetype -lglfw3 -lopengl32 -lgdi32   

program.o: program.cpp
	g++ -c -Wall -Wextra -std=c++14 -pedantic program.cpp -o program.o

glad.o: glad.c
	g++ -c glad.c -o glad.o

resourceManager.o: resourceManager.cpp
	g++ -c -Wall -Wextra -std=c++14 -pedantic resourceManager.cpp -o resourceManager.o

shader.o: shader.cpp
	g++ -c -Wall -Wextra -std=c++14 -pedantic shader.cpp -o shader.o

texture.o: texture.cpp
	g++ -c -Wall -Wextra -std=c++14 -pedantic texture.cpp -o texture.o

game.o: game.cpp
	g++ -c -Wall -Wextra -std=c++14 -pedantic game.cpp -o game.o

spriteRenderer.o: spriteRenderer.cpp
	g++ -c -Wall -Wextra -std=c++14 -pedantic spriteRenderer.cpp -o spriteRenderer.o

gameObject.o: gameObject.cpp
	g++ -c -Wall -Wextra -std=c++14 -pedantic gameObject.cpp -o gameObject.o


ballObject.o: ballObject.cpp
	g++ -c -Wall -Wextra -std=c++14 -pedantic ballObject.cpp -o ballObject.o

Particle_gen.o: Particle_gen.cpp
	g++ -c -Wall -Wextra -std=c++14 -pedantic Particle_gen.cpp -o Particle_gen.o

textRenderer.o: textRenderer.cpp
	g++  -I./freetype -c textRenderer.cpp -o textRenderer.o 
clean:
	rm -f *.exe *.o
