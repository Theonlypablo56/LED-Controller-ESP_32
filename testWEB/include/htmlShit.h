#pragma

const char* mainPage = R"(
  <!DOCTYPE html>
  <html lang='en'>
    <head>

      <style>
        body {
          background: #556b2f;
          color: #ffebcd;
        }

        .textShit {
          margin-top: 0%;
          margin-left: 5%;
          font-size: x-large;
          color: #ffebcd;
        }

        .header {
          font-size: xxx-large;
          margin: 2%;
          text-align: start;
        }

        .button {
          background-color: #04AA6D;
          border: none;
          color: white;
          padding: 15px 32px;
          text-align: center;
          text-decoration: none;
          display: inline-block;
          font-size: 16px;
          margin: 4px 2px;
          cursor: pointer;
        }

        .buttonor button{
          display: inline-block;
          font-size: 15px;
          margin-left: 0px;
          background: rgb(133, 64, 64);
          border: none;
        }
      </style>

      <title> Penor </title>
    </head>
    
    <body>
      <h1 id='penisTitle' class='header'> My Penis :D </h1>
      
      <h5 class='textShit'> The button below touches my penis so please try to stay away from it </h5>
      <div id='buttons' class='buttonor'>
        <button id='penisTouchButton' onclick='penisFunction()' style='margin-left: 15%;'> touch </button>
        <button id='penisUntouchButton' style='opacity: 0;' onclick='unTouchFunction()' disabled> UNTOUCH </button>
        
        <button id='colorPickerLinker' onclick='rgbRedirect()'> Color picker zone </button>
      </div>

    </body>
    <script>
    //let start = Date.now();
    let touched = false;

    let penisFunction = () => {
      touched = true;
      let title = document.getElementById('penisTitle');
      title.textContent = 'PENIS BUTTON HAS BEEN TOUCHED !';
      title.style.color = 'red';
      let otherButton = document.getElementById('penisUntouchButton');
      otherButton.disabled = false;
      otherButton.style.opacity = 100;
      //console.log(otherButton);
      var innty = setInterval(() => {
        if (touched == false){
          clearInterval(innty);
          return;
        }
        var tempOp = otherButton.style.opacity;
        console.log(tempOp);
        otherButton.style.opacity = (tempOp == 0) ? 100 : 0;
      }, 100);
    }
    
    let unTouchFunction = () => {
      touched = false;
      let title = document.getElementById('penisTitle');
      title.textContent = 'nvm we good its untouched :D';
      title.style.color = 'black';
      document.getElementById('penisUntouchButton').style.opacity = 0;
    }

    let rgbRedirect = () => {
      //window.location.href = 'otherPages/peenor.html';
      window.location.href = '/penisMwahaha';
    }

    
    </script>
  </html>
)";

// - - - - - - - - - - - - - - - - - - - - - -

const char* secondPage = R"(
  <!DOCTYPE html>
  <html lang='en'>
  <head>
    <style>
      body {
        margin: 30px;
        background: 	#565656;
        color: 		#efedf3;
      }

      input.rgbInput{
        width: 200px;
        height: 200px;
        border-color: transparent;
        border-width: 0px;
        padding: 0px 0px 0px 0px;
        background-color: #17141400;
      }
      .inputLabel{
        text-align: center;
        width: fit-content;
        border-color: transparent;
        border-width: 0px;
      }
      .adjustables{
        margin-left: 30px;
        position: relative;
      }
      .container{
        display:flex;
        width: 195px;
        flex-direction:column;
        align-items:center;
        justify-content:center;
      }

      .topNav{
        float: left;
        color: #f2f2f2;
        text-align: center;
        padding: 14px 12px;
        text-decoration: none;
        font-size: 17px;
      }
    </style>

    <script>
      setTimeout( () => {
        let colorPicker = document.getElementById('RGBCOLOR');
        let hertzInput = document.getElementById('hertzInput');

        let currHertz = 11500;
        let currBitch = true;

        colorPicker.addEventListener('change', () => {
          const rgbVal = hexDecoder(colorPicker.value);
          console.log(rgbVal);

          var xhttp = new XMLHttpRequest();
          
          xhttp.open("POST", "updatedRGB?Value="+rgbVal, true);
          xhttp.send();
        });
        
        hertzInput.addEventListener('change', () => {
          const hertzVal = hertzInput.value;
          console.log(hertzVal);

          var xhttp = new XMLHttpRequest();
          
          xhttp.open("POST", "updatedHertz?Value="+hertzVal, true);
          xhttp.send();
        });

        
        var balls = new XMLHttpRequest();
        balls.open("GET", "text/plain", true);
        balls.addEventListener('load', () => {
          console.log(balls.responseText);
        });
        balls.send();
        
      }, 100);

      let hexDecoder = (hexCode) => {
        let r = (letToNum(hexCode[1]) * 16) + letToNum(hexCode[2]);
        let g = (letToNum(hexCode[3]) * 16) + letToNum(hexCode[4]);
        let b = (letToNum(hexCode[5]) * 16) + letToNum(hexCode[6]);
        //console.log(`(${r}, ${g}, ${b})`);
        return `${r},${g},${b}`
      }

      let letToNum = (str) => {
        if (Number(str)){
          return Number(str);
        }
        str.toLowerCase();
        switch (str) {
          case 'a':
            str = 10;
            break;
          case 'b':
            str = 11;
            break;
          case 'c':
            str = 12;
            break;
          case 'd':
            str = 13;
            break;
          case 'e':
            str = 14;
            break;
          case 'f':
            str = 15;
            break;
          default:
            str = Number(str);
        }
        return str;
      }

    </script>
  <title> colors </title>
  </head>
  <body>
    <div class="topNav">
      Woah 
    </div>

    <h1 id='colorTitle'> The Color Title </h1>
    
    <h5>Pick ur LED color pls.</h5>
    
    <div class="adjustables">

      <div class="container">
        <label for "COLOR" class="inputLabel" style="background-color: #50561a;">#50561a</label>
        <input type='color' id='RGBCOLOR' class="rgbInput" name='COLOR' value='#50561a'/>
      </div>
      
      <input type="number" id="hertzInput" name="HERTZ" placeholder="Currently set to 11,500hz"/>
    </div>
    
  </body>
  </html>
)";