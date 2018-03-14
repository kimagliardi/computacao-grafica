Lista de Exercícios 1 – Computação Gráfica

**Introdução à OpenGL Moderna – Shaders, VBO, VAO**
1. Leitura OBRIGATÓRIA para começar:

- https://learnopengl.com/#!Getting-started/Hello-Triangle

- https://learnopengl.com/#!Getting-started/Shaders

- http://antongerdelan.net/opengl/hellotriangle.html
2. Analise o código fonte e tente fazer a relação dos conceitos de shaders, VBOs e VAO 
    - **VBO**: Pelo que entendi, VBO é o buffer de memória que mantém os dados com informações sobre os vértices, é interessante utilizá-lo como buffer para placa gráfica pois seu acesso é rápido (mais rápido do que por exemplo, acessar a memória principal);
    
    - **Shader**: Shaders são programas "C-like" estcritos para especificação GLSL, é o código que comanda o funcionamento das etapas programáveis da **GPU**.
    
    - **VAO**: É o buffer para informações sobre os objetos dos vértices, é desenhado apra aarmazenar informações de renderização do objeto, no nosso exemplo, cores.
apresentados até então.
3. Faça o passo-a-passo para criar o triângulo com cores diferentes em cada vértice 
    - Pressionar a tecla **T**
4. Faça o desenho de 2 triângulos na tela
    - Pressionar a tecla **X**
5. Faça o desenho de um círculo na tela
    - Pressionar a tecla **C**

6. Implemente (pode pegar do tutorial) uma classe para tratar os shaders a partir de
arquivos


Entrega individual via Moodle (consulte a data de entrega no sistema)