import Map from 'ol/Map';
import View from 'ol/View';
import TileLayer from 'ol/layer/Tile';
import XYZ from 'ol/source/XYZ';
import { fromLonLat } from 'ol/proj';
import 'ol/ol.css';

//import {getPlanetApiKey} from './login.js'

const map = new Map({
 target: 'map',
 layers: [
   new TileLayer({
     source: new XYZ({
       url: 'https://{a-c}.tile.openstreetmap.org/{z}/{x}/{y}.png'
     })
   })
 ],
 view: new View({
   center: fromLonLat([-122.2730, 37.8715]),
   zoom: 12
 })
});
