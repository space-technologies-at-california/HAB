(window["webpackJsonp"] = window["webpackJsonp"] || []).push([[6],{

/***/ "./node_modules/ol/node_modules/geotiff/src/compression/deflate.js":
/*!*************************************************************************!*\
  !*** ./node_modules/ol/node_modules/geotiff/src/compression/deflate.js ***!
  \*************************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"default\", function() { return DeflateDecoder; });\n/* harmony import */ var pako__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! pako */ \"./node_modules/ol/node_modules/pako/dist/pako.esm.mjs\");\n/* harmony import */ var _basedecoder__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./basedecoder */ \"./node_modules/ol/node_modules/geotiff/src/compression/basedecoder.js\");\n\n\n\nclass DeflateDecoder extends _basedecoder__WEBPACK_IMPORTED_MODULE_1__[\"default\"] {\n  decodeBlock(buffer) {\n    return Object(pako__WEBPACK_IMPORTED_MODULE_0__[\"inflate\"])(new Uint8Array(buffer)).buffer;\n  }\n}\n\n\n//# sourceURL=webpack:///./node_modules/ol/node_modules/geotiff/src/compression/deflate.js?");

/***/ })

}]);