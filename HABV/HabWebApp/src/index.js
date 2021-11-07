import Map from 'ol/Map';
import View from 'ol/View';
import TileLayer from 'ol/layer/Tile';
import XYZ from 'ol/source/XYZ';
import Feature from 'ol/Feature';
import Point from 'ol/geom/Point';
import { fromLonLat, useGeographic } from 'ol/proj';
import VectorSource from 'ol/source/Vector';
import VectorLayer from 'ol/layer/Vector';
import Circle from 'ol/style/Circle';
import Fill from 'ol/style/Fill';
import Style from 'ol/style/Style';
import 'ol/ol.css';

//import {getPlanetApiKey} from './login.js'

// function plotPoint(lon, lat) {
//   return fromLonLat([lon, lat]);
// }


/**
Takes a data point and returns the location
**/
function getLocationFromData(dataPoint){
  return fromLonLat([dataPoint.lon, dataPoint.lat]);
}

/**
Takes an array of data points and returns an array of Feature objects of plottable points
**/
function getFeaturesFromData(dataArray){
  const res = [];
  for(let i = 0; i < dataArray.length; i++){
    res[i] = new Feature(new Point(getLocationFromData(dataArray[i])));
  }
  return res;
}

//Constants For testing
//const point = new Point(plotPoint(-122.2730, 37.8715));
var dataOne = {
  lon: -122.2730,
  lat: 37.8715
}
var dataTwo = {
  lon: -122.3,
  lat: 37.8715
}
var dataThree = {
  lon: -122.35,
  lat: 37.8715

}
const data = [dataOne, dataTwo, dataThree];

//Map object that is plotted
const map = new Map({
 target: 'map',
 layers: [
   new TileLayer({
     source: new XYZ({
       url: 'https://{a-c}.tile.openstreetmap.org/{z}/{x}/{y}.png'
     })
   }),
   new VectorLayer({
    source: new VectorSource({
      features: getFeaturesFromData(data),
    }),
    style: new Style({
      image: new Circle({
        radius: 8,
        fill: new Fill({color: 'red'}),
      }),
    }),
  }),
 ],
 view: new View({
   center: fromLonLat([-122.2730, 37.8715]),
   zoom: 12
 })
});
