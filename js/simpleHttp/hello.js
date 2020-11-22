// 一个简单的Http服务
"use strict";

// 导入node自带的http模块
var http = require("http");

// 创建http server，并传入回调函数
var server = http.createServer(function (request, response) {
    // 回调函数接受request 和 response对象
    // 获得HTTP请求的method和url
    console.log(request.method + ": " + request.url);

    // 将HTTP响应200写入response
    response.writeHead(200, { "Content-Type": "text/html" });
    response.end("<h1>Hello world</h1>");
});

server.listen(8080);
console.log("Server is running at http://127.0.0.1:8080");
