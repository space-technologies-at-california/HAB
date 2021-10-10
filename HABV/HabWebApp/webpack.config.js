const path = require('path');

module.exports = {
  mode: 'development',
  entry: {
    index: './src/index.js',
//    login: './src/login.js',
  },
  module: {
    rules: [
      { test: /\.css$/, use: ["style-loader","css-loader"] },
      { test: /\.(png|svg|jpe?g|gif|woff2?|ttf|eot)$/, use: [ 'file-loader' ] },
    ],
  },
  output: {
    filename: '[name].js',
    path: path.resolve(__dirname, 'dist'),
  },
  devServer: {
    contentBase: path.join(__dirname, 'dist'),
    compress: true,
    port: 9000
  }
};
