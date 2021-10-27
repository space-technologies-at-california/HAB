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

const place = [-122.2730, 37.8715];

const point = new Point(place);

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
      features: [new Feature(point)],
    }),
    style: new Style({
      image: new Circle({
        radius: 20,
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
