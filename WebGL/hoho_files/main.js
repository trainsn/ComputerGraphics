;(function() {
    document.addEventListener('DOMContentLoaded', function() {
        //---canvas2d
       /* var canvas2d = document.getElementById('canvas2d');
        var ctx = canvas2d.getContext('2d');
        log(ctx);

        // 黑色背景
        ctx.fillStyle = 'rgba(0, 0, 0, 1)';
        ctx.fillRect(0, 0, canvas2d.width, canvas2d.height);
        // 紫色矩形
        ctx.fillStyle = 'rgba(255, 0, 255, 0.75)';
        ctx.fillRect(100, 100, 200, 200);
*/

        //---webgl
        var webgl = document.getElementById('webgl');
        var gl = webgl.getContext('experimental-webgl');
        log(gl);

        // 指定清空canvas的颜色
        // 参数是rgba，范围0.0~1.0
        gl.clearColor(0.0, 0.0, 0.0, 1.0);
        // 清空canvas
        // gl.COLOR_BUFFER_BIT颜色缓存，默认清空色rgba(0.0, 0.0, 0.0, 0.0) 透明黑色，通过gl.clearColor指定
        // gl.DEPTH_BUFFER_BIT深度缓存，默认深度1.0，通过gl.clearDepth指定
        // gl.STENCIL_BUFFER_BIT模板缓存，默认值0，通过gl.clearStencil()指定
        gl.clear(gl.COLOR_BUFFER_BIT);
        
        // 绘制矩形
        // 0.着色器源程序
        // 顶点着色器源程序
        var vsSrc = 'void main() {' +
            'gl_Position = vec4(0.0, 0.0, 0.0, 1.0);' + // 设置坐标
            'gl_PointSize = 200.0;' +                   // 设置尺寸
        '}';
        // 片元着色器源程序
        var fsSrc = 'void main() {' +
            'gl_FragColor = vec4(1.0, 0.0, 1.0, 0.75);' + // 设置颜色
        '}';
        // 初始化着色器
        // 1.创建着色器对象
        var vs = gl.createShader(gl.VERTEX_SHADER);
        var fs = gl.createShader(gl.FRAGMENT_SHADER);
        // 检查创建结果
        if (vs === null) {
            log('gl.createShader(gl.VERTEX_SHADER) failed');
        }
        if (fs === null) {
            log('gl.createShader(gl.FRAGMENT_SHADER) failed');
        }
        // 2.填充源程序
        gl.shaderSource(vs, vsSrc);
        gl.shaderSource(fs, fsSrc);
        // 3.编译
        gl.compileShader(vs);
        gl.compileShader(fs);
        // 检查编译错误
        if (!gl.getShaderParameter(vs, gl.COMPILE_STATUS)) {
            log('gl.compileShader(vs) failed');
            log(gl.getShaderInfoLog(vs));   // 输出错误信息
        }
        if (!gl.getShaderParameter(fs, gl.COMPILE_STATUS)) {
            log('gl.compileShader(fs) failed');
            log(gl.getShaderInfoLog(fs));   // 输出错误信息
        }
        // 4.创建程序对象
        var prog = gl.createProgram();
        // 检查创建结果
        if (prog === null) {
            log('gl.createProgram() failed');
        }
        // 5.为程序对象分配着色器
        gl.attachShader(prog, vs);
        gl.attachShader(prog, fs);
        // 检查分配错误
        if (gl.getProgramParameter(prog, gl.ATTACHED_SHADERS) !== 2) {
            log('gl.getProgramParameter(prog, gl.ATTACHED_SHADERS) failed');
        }
        // 6.连接程序对象
        gl.linkProgram(prog);
        // 检查连接错误
        if (!gl.getProgramParameter(prog, gl.LINK_STATUS)) {
            log('gl.linkProgram(prog) failed');
            log(gl.getProgramInfoLog(prog));
        }
        // 7.使用程序对象
        gl.useProgram(prog);

        // 绘制矩形（一个点，但点的尺寸略大）
        gl.drawArrays(gl.POINTS, 0, 1);
    });

    function log() {
        Array.prototype.slice.call(arguments).forEach(function(item) {
            console.log(item);
        });
    }
})();