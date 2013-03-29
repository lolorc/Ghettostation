
boolean antenna_tracking() {
// Tracking general function

	
	float rel_alt = uav_alt - home_alt; // relative altitude to ground in meters
	
	calc_tracking( home_lon, home_lat, uav_lon, uav_lat, rel_alt); //calculate tracking bearing/azimuth
	
	//set current GPS bearing relative to home_bearing
	
	if(Bearing > home_bearing){
          Bearing=(Bearing-home_bearing);
          return true;
        }
        else
        {
          Bearing=(360-home_bearing+Bearing);
          return true;
        }
	// serv command
	
	servoPathfinder(Bearing,Azimuth);
	
	

}



long calc_tracking(float lon1, float lat1, float lon2, float lat2, float alt) {
// (homelon, homelat, uavlon, uavlat, uavalt ) 
// Return Bearing & Azimuth angles in degree
  float a, tc1, R, c, d, dLat, dLon;
 
 // converting to radian
  lon1=toRad(lon1);
  lat1=toRad(lat1);
  lon2=toRad(lon2);
  lat2=toRad(lat2);
 
 
 //calculating bearing in degree decimal
  Bearing = calc_bearing(lon1,lat1,lon2,lat2);

 
//calculating distance between uav & home
  Azimuth = calc_azimuth(lon1,lat1,lon2,lat2,alt);
 
}


long calc_bearing(float lon1, float lat1, float lon2, float lat2) {
// bearing calc, feeded in radian, output degrees
	float a;
	//calculating bearing in degree
	a=atan2(sin(lon2-lon1)*cos(lat2), cos(lat1)*sin(lat2)-sin(lat1)*cos(lat2)*cos(lon2-lon1));
	a=toDeg(a);
	if (a<0) a=360+a;
	return a;
}

long calc_azimuth(float lon1, float lat1, float lon2, float lat2, float alt) {
//Azimuth cacl, feeded in radian, output in degrees
  float a, az, c, d, R, dLat, dLon;
  //calculating distance between uav & home
  R=6371000.0;    //earth radius 6371km
  dLat = (lat2-lat1);
  dLon = (lon2-lon1);
  a = sin(dLat/2) * sin(dLat/2) + sin(dLon/2) * sin(dLon/2) * cos(lat1) * cos(lat2); 
  c = 2* asin(sqrt(a));  
  d = R * c;
  az=atan(alt/d);// in radian
  az=toDeg(az); // in degree
  return az;
}

long toRad(float angle) {
// convert degrees to radians
	angle = angle/180*PI;
	return angle;
}

long toDeg(float angle) {
// convert radians to degrees.
	angle = angle*180/PI;
}
	

