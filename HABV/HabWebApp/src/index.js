import Map from 'ol/Map';
import View from 'ol/View';
import TileLayer from 'ol/layer/Tile';
import XYZ from 'ol/source/XYZ';
import Feature from 'ol/Feature';
import Point from 'ol/geom/Point';
import { fromLonLat, toLonLat } from 'ol/proj';
import VectorSource from 'ol/source/Vector';
import VectorLayer from 'ol/layer/Vector';
import Circle from 'ol/style/Circle';
import Fill from 'ol/style/Fill';
import Style from 'ol/style/Style';
import Overlay from 'ol/Overlay';
import { toStringHDMS } from 'ol/coordinate';
import 'ol/ol.css';

// import {getPlanetApiKey} from './login.js'

// function plotPoint(lon, lat) {
//   return fromLonLat([lon, lat]);
// }


// Takes a data point and returns the location
function getLocationFromData(dataPoint) {
  return fromLonLat([dataPoint.lon, dataPoint.lat]);
}

// Takes an array of data points and returns an array of Feature objects of plottable points
function getFeaturesFromData(dataArray) {
  const res = [];
  for (let i = 0; i < dataArray.length; i++) {
    res[i] = new Feature(new Point(getLocationFromData(dataArray[i])));
  }
  return res;
}

// Constants for testing
var dataOne = {
  lon: -122.27,
  lat: 37.87
}

var dataTwo = {
  lon: -122.30,
  lat: 37.87
}

var dataThree = {
  lon: -122.35,
  lat: 37.87
}

const data = [dataOne, dataTwo, dataThree];

// Map object that is plotted
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
          radius: 10,
          fill: new Fill({ color: 'green' }),
        }),
      }),
    }),
  ],
  view: new View({
    center: fromLonLat([-122.2730, 37.8715]),
    zoom: 12
  })
});

// Popup showing the position the user clicked
const popup = new Overlay({
  element: document.getElementById('popup'),
});
map.addOverlay(popup);

map.on('click', function (evt) {
  console.log('clicked!');
  const element = popup.getElement();
  const coordinate = evt.coordinate;
  const [dataLon, dataLat] = toLonLat(coordinate);
  const hdms = toStringHDMS([dataLon, dataLat]);

  $(element).popover('dispose');
  popup.setPosition(coordinate);
  
  $(element).popover({
    container: element,
    placement: 'top',
    animation: false,
    html: true,
    content: '<p>The location you clicked was:</p><code>' + hdms + '</code>',
  });

  if (map.hasFeatureAtPixel(evt.pixel) == true) {
    $(element).popover('show');
  } else {
    $(element).popover('hide');
  }
});


