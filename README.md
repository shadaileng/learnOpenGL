# learnOpenGL
整合了Light、Camera、Mesh、Model和Shader类  
***
* main中实现了从文本文件中加载light和model；  
***
* light指针传入Model中并由该model的shader发送到片段着色器；  
***
* model加载模型时获得其mesh，绘制时遍历所有mesh的draw方法；  
***
