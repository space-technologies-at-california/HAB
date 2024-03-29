(window["webpackJsonp"] = window["webpackJsonp"] || []).push([[4],{

/***/ "./node_modules/ol/node_modules/geotiff/src/compression/basedecoder.js":
/*!*****************************************************************************!*\
  !*** ./node_modules/ol/node_modules/geotiff/src/compression/basedecoder.js ***!
  \*****************************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"default\", function() { return BaseDecoder; });\n/* harmony import */ var _predictor__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ../predictor */ \"./node_modules/ol/node_modules/geotiff/src/predictor.js\");\n\n\nclass BaseDecoder {\n  async decode(fileDirectory, buffer) {\n    const decoded = await this.decodeBlock(buffer);\n    const predictor = fileDirectory.Predictor || 1;\n    if (predictor !== 1) {\n      const isTiled = !fileDirectory.StripOffsets;\n      const tileWidth = isTiled ? fileDirectory.TileWidth : fileDirectory.ImageWidth;\n      const tileHeight = isTiled ? fileDirectory.TileLength : (\n        fileDirectory.RowsPerStrip || fileDirectory.ImageLength\n      );\n      return Object(_predictor__WEBPACK_IMPORTED_MODULE_0__[\"applyPredictor\"])(\n        decoded, predictor, tileWidth, tileHeight, fileDirectory.BitsPerSample,\n        fileDirectory.PlanarConfiguration,\n      );\n    }\n    return decoded;\n  }\n}\n\n\n//# sourceURL=webpack:///./node_modules/ol/node_modules/geotiff/src/compression/basedecoder.js?");

/***/ }),

/***/ "./node_modules/ol/node_modules/geotiff/src/compression/raw.js":
/*!*********************************************************************!*\
  !*** ./node_modules/ol/node_modules/geotiff/src/compression/raw.js ***!
  \*********************************************************************/
/*! exports provided: default */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"default\", function() { return RawDecoder; });\n/* harmony import */ var _basedecoder__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! ./basedecoder */ \"./node_modules/ol/node_modules/geotiff/src/compression/basedecoder.js\");\n\n\n\nclass RawDecoder extends _basedecoder__WEBPACK_IMPORTED_MODULE_0__[\"default\"] {\n  decodeBlock(buffer) {\n    return buffer;\n  }\n}\n\n\n//# sourceURL=webpack:///./node_modules/ol/node_modules/geotiff/src/compression/raw.js?");

/***/ }),

/***/ "./node_modules/ol/node_modules/geotiff/src/predictor.js":
/*!***************************************************************!*\
  !*** ./node_modules/ol/node_modules/geotiff/src/predictor.js ***!
  \***************************************************************/
/*! exports provided: applyPredictor */
/***/ (function(module, __webpack_exports__, __webpack_require__) {

"use strict";
eval("__webpack_require__.r(__webpack_exports__);\n/* harmony export (binding) */ __webpack_require__.d(__webpack_exports__, \"applyPredictor\", function() { return applyPredictor; });\n\nfunction decodeRowAcc(row, stride) {\n  let length = row.length - stride;\n  let offset = 0;\n  do {\n    for (let i = stride; i > 0; i--) {\n      row[offset + stride] += row[offset];\n      offset++;\n    }\n\n    length -= stride;\n  } while (length > 0);\n}\n\nfunction decodeRowFloatingPoint(row, stride, bytesPerSample) {\n  let index = 0;\n  let count = row.length;\n  const wc = count / bytesPerSample;\n\n  while (count > stride) {\n    for (let i = stride; i > 0; --i) {\n      row[index + stride] += row[index];\n      ++index;\n    }\n    count -= stride;\n  }\n\n  const copy = row.slice();\n  for (let i = 0; i < wc; ++i) {\n    for (let b = 0; b < bytesPerSample; ++b) {\n      row[(bytesPerSample * i) + b] = copy[((bytesPerSample - b - 1) * wc) + i];\n    }\n  }\n}\n\nfunction applyPredictor(block, predictor, width, height, bitsPerSample,\n  planarConfiguration) {\n  if (!predictor || predictor === 1) {\n    return block;\n  }\n\n  for (let i = 0; i < bitsPerSample.length; ++i) {\n    if (bitsPerSample[i] % 8 !== 0) {\n      throw new Error('When decoding with predictor, only multiple of 8 bits are supported.');\n    }\n    if (bitsPerSample[i] !== bitsPerSample[0]) {\n      throw new Error('When decoding with predictor, all samples must have the same size.');\n    }\n  }\n\n  const bytesPerSample = bitsPerSample[0] / 8;\n  const stride = planarConfiguration === 2 ? 1 : bitsPerSample.length;\n\n  for (let i = 0; i < height; ++i) {\n    // Last strip will be truncated if height % stripHeight != 0\n    if (i * stride * width * bytesPerSample >= block.byteLength) {\n      break;\n    }\n    let row;\n    if (predictor === 2) { // horizontal prediction\n      switch (bitsPerSample[0]) {\n        case 8:\n          row = new Uint8Array(\n            block, i * stride * width * bytesPerSample, stride * width * bytesPerSample,\n          );\n          break;\n        case 16:\n          row = new Uint16Array(\n            block, i * stride * width * bytesPerSample, stride * width * bytesPerSample / 2,\n          );\n          break;\n        case 32:\n          row = new Uint32Array(\n            block, i * stride * width * bytesPerSample, stride * width * bytesPerSample / 4,\n          );\n          break;\n        default:\n          throw new Error(`Predictor 2 not allowed with ${bitsPerSample[0]} bits per sample.`);\n      }\n      decodeRowAcc(row, stride, bytesPerSample);\n    } else if (predictor === 3) { // horizontal floating point\n      row = new Uint8Array(\n        block, i * stride * width * bytesPerSample, stride * width * bytesPerSample,\n      );\n      decodeRowFloatingPoint(row, stride, bytesPerSample);\n    }\n  }\n  return block;\n}\n\n\n//# sourceURL=webpack:///./node_modules/ol/node_modules/geotiff/src/predictor.js?");

/***/ })

}]);