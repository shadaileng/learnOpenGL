# learnOpenGL
整合了Light、Camera、Mesh、Model和Shader类  
***
* main中实现了从文本文件中加载light和model；  
***
* light指针传入Model中并由该model的shader发送到片段着色器；  
***
* model加载模型时获得其mesh，绘制时遍历所有mesh的draw方法；  
* model类的models数组属性接受模型的多个组合变换，并将其作为顶点属性发送到顶点着色器；   
***
* mesh类添加一个添加模型变换的顶点属性方法；  
***
* shader类添加几何着色器的支持  
***
* 顶点着色器输出为接口块；  
* 几何着色器的输入为接口块数组，输出为接口块；  
* 片段着色器的输入为接口块，输出为vec4颜色值；  
***
* 
