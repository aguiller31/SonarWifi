#include "Server_Service.h"
#include <Arduino.h>
ServerService::ServerService():server(80),events("/events")
{

}
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="fr">
<head>
  <meta charset="UTF-8">
  <title>Radar</title>
</head>
<body>
  <canvas id="sonarCanvas" width="905" height="905"></canvas>
<style>
        body {
            margin: 0;
            height: 100vh;
            display: flex;
            justify-content: center;
            align-items: center;
			background:black;
        }

        canvas {
            border: 1px solid #000; /* optional: add a border to the canvas */
        }
    </style>
  <script>
const canvas = document.getElementById('sonarCanvas');
const ctx = canvas.getContext('2d');
const needleLength = 450; // Longueur de l'aiguille
const sonarRadius = 450; // Rayon du sonar
const pointDuration = 3000; // Durée d'affichage du point en millisecondes
const ringSpacing = 50; // Espacement entre les anneaux en pixels (correspond à 50 mm)
const diameterSpacing = 30; // Espacement entre les diamètres en degrés
let isPointVisible = false;
let point = { x: 0, y: 0 };
let trail = [];
let rotateNeedle = true;
let start =false;
var points =[];
var simN = 140;
// Fonction pour convertir des degrés en radians
function degreesToRadians(degrees) {
    return (degrees * Math.PI) / 180;
}
// Fonction pour dessiner le sonar, l'aiguille, les anneaux et le point
let rotIntervalCnt = 0;
let rotInterval;
function startNeedleSpin(){
    rotInterval = setInterval(function(){
    rotIntervalCnt++;
},28);
}
function drawSonar() {
 if (rotateNeedle) {
const rotationAngle = (rotIntervalCnt*0.099) % 360; // Rotation basée sur le temps
    const angle = degreesToRadians(rotationAngle);
    const needleX = canvas.width / 2 + needleLength * Math.cos(angle);
    const needleY = canvas.height / 2 + needleLength * Math.sin(angle);

    // Fond vert pour le sonar
    ctx.fillStyle = '#000000';
    ctx.fillRect(0, 0, canvas.width, canvas.height);

   // Dessiner les anneaux blancs avec les étiquettes de distance
    ctx.beginPath();
    for (let r = ringSpacing; r <= sonarRadius; r += ringSpacing) {
        ctx.arc(canvas.width / 2, canvas.height / 2, r, 0, 2 * Math.PI);

        // Afficher la distance
        const distanceText = `${r} mm`;
        const textX = canvas.width / 2 + r + 5; // Adjust the distance from the circle
        const textY = canvas.height / 2 - 10;
        ctx.fillStyle = '#FFF';
        ctx.fillText(distanceText, textX, textY);
    }
    ctx.strokeStyle = '#FFF';
    ctx.stroke();


	 ctx.beginPath();
    for (let angle = 0; angle < 360; angle += diameterSpacing) {
        const radians = degreesToRadians(angle);
        const startX = canvas.width / 2;
        const startY = canvas.height / 2;
        const endX = canvas.width / 2 + sonarRadius * Math.cos(radians);
        const endY = canvas.height / 2 + sonarRadius * Math.sin(radians);
        ctx.moveTo(startX, startY);
        ctx.lineTo(endX, endY);
		// Afficher l'angle
        const angleText = `${angle}°`;
        const textX = canvas.width / 2 + sonarRadius * 1.1 * Math.cos(radians); // Adjust the distance from the diameter
        const textY = canvas.height / 2 + sonarRadius * 1.1 * Math.sin(radians);
        ctx.fillStyle = '#FFF';
        ctx.fillText(angleText, textX, textY);
		
    }
    ctx.strokeStyle = '#FFF';
    ctx.stroke();
	
    // Dessiner le cercle du sonar
    ctx.beginPath();
    ctx.arc(canvas.width / 2, canvas.height / 2, sonarRadius, 0, 2 * Math.PI);
    ctx.strokeStyle = '#000';
    ctx.stroke();
	
 // Dessiner la trace de l'aiguille (lignes reliant toutes les positions)
   // Dessiner la trace du rayon (ligne reliant toutes les positions)
    for (let i = 1; i < trail.length; i++) {
        ctx.beginPath();
        ctx.moveTo(canvas.width / 2, canvas.height / 2);
        ctx.lineTo(trail[i].x, trail[i].y);
        ctx.strokeStyle = 'rgba(0, 255, 0, '+(i / trail.length)+')'; // Ajustez la couleur et l'opacité ici
        ctx.stroke();
    }

    // Dessiner le rayon tournant avec une opacité réduite
   

    // Ajouter la position actuelle du rayon à la trace
    trail.push({ x: needleX, y: needleY });

    // Limiter la longueur de la trace pour éviter une accumulation infinie
    if (trail.length > 800) {
        trail.shift();
    }

    // Dessiner le point s'il est visible
    for (let i = 1; i < points.length; i++) {
     
        // Dessiner le halo
        if(points[i]){
        ctx.beginPath();
        ctx.arc(points[i].x, points[i].y, 10, 0, 2 * Math.PI);
        ctx.fillStyle = 'rgba(255, 0, 0, 0.2)'; // Opacité du halo
        ctx.fill();

        // Dessiner le point
       
        ctx.beginPath();
        ctx.arc(points[i].x, points[i].y, 10/3, 0, 2 * Math.PI);
        ctx.fillStyle = 'red';
        ctx.fill();
        }
        }
    
}
}
// Fonction pour placer le point à partir d'un angle et d'une distance
// Fonction pour placer le point à partir d'un angle et d'une distance
function placePoint(angle, distance) {
angle = degreesToRadians(angle);
    const x = distance * Math.cos(angle);
    const y = distance * Math.sin(angle);

    point.x = canvas.width / 2 + x;
    point.y = canvas.height / 2 + y;
    points[simN%360] = {x:point.x, y:point.y};
   /* isPointVisible = true;
    drawSonar();

    // Masquer le point après la durée spécifiée
    setTimeout(() => {
        isPointVisible = false;
        drawSonar();
    }, pointDuration);*/
}


// Mettre à jour le canvas à intervalles réguliers
function updateCanvas() {
    drawSonar();
    //requestAnimationFrame(updateCanvas);
}

// Démarrer la mise à jour du canvas
//updateCanvas();

// Exemple d'utilisation : placer un point à un angle aléatoire et une distance aléatoire

function toggleRotation() {
    rotateNeedle = !rotateNeedle;
}

if (!!window.EventSource) {
 var source = new EventSource('/events');
 
 source.addEventListener('open', function(e) {
  console.log("Events Connected");
 }, false);
 source.addEventListener('error', function(e) {
  if (e.target.readyState != EventSource.OPEN) {
    console.log("Events Disconnected");
  }
 }, false);
 
 source.addEventListener('message', function(e) {
  console.log("message", e.data);
 }, false);
 
 source.addEventListener('d',distanceDeal, false);

 source.addEventListener('a', angleDeal, false);

 
}

function angleDeal(e){
    if(!start){
    rotIntervalCnt=(e.data)/0.099;
    start=true;
    startScanInt();
    startNeedleSpin();
  }
  console.log("a", e.data);
  placePoint(e.data,dist);
  simN++;
 //placePoint(e.data,dist);
}
function distanceDeal(e){
    console.log("d", e.data);
  dist = e.data;
}
/*
function simulate(){

    distanceDeal({
        data: Math.floor(Math.random() * 400) + 1
    });
    angleDeal({
       data:simN
    });
    
}*/
    setInterval(simulate,283);
    function startScanInt(){
        setInterval(updateCanvas,283/10);
    }
    
  </script>
</body>
</html>)rawliteral";
String processor(const String& var){
  return String();
}
void ServerService::setup()
{
  this->server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Handle Web Server Events
  this->events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
  });
  this->server.addHandler(&events);
}

void ServerService::start()
{
   this->server.begin();                           // Actually start the server
  Serial.println("HTTP server started");
}
void ServerService::sendEvent(char c, int distance)
{
  events.send("ping",NULL,millis());

  
  events.send(String(distance).c_str(),String(c).c_str(),millis());
}
