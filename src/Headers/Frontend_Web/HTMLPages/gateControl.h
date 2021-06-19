// ********************************************************************************************
//                                 Project - Gate Control                                       
// --------------------------------------------------------------------------------------------
//
// File  : gateControl.h
// Author: Gabriel da Silva Caetano <98gabrielSc@gmail.com>
//
// ********************************************************************************************

// ----------------------------------------------------------------------------------------- //

#ifndef _HTML_PAGE_GATE_CONTROL_H
#define _HTML_PAGE_GATE_CONTROL_H

// ----------------------------------------------------------------------------------------- //

const char htmlPageGateControl[] PROGMEM = R"rawliteral(
  <head>
    <title>Gate Control</title>
    <meta name='viewport' content='width=device-width, initial-scale=1' charset='UTF-8'>
    <style>
      html {
        font-family: Calibri; 
        margin: 0; padding: 0;
      }
      .centralize {
        left: 50%; top: 50%; 
        transform: translate(-50%, -50%);
      }
      .centerItens {
        justify-content: center;
        align-items: center;
        text-align: center;
      }
      .aling {
        flex: 1; display: flex;
        flex-direction: column;
      }
      .mainContainer { 
        position: absolute;
        border-radius: 4px;
        box-shadow: 0 0 6px #015356; 
        width: 98%; height: 98%;
        max-width: 850px;
        max-height: 850px;
        overflow: scroll;
      }
      button {
        outline: none;
        cursor: pointer; 
        color: white; 
        border: none;
        border-radius: 6px;
        background-color: #53BD38;
        box-shadow: 0 0 1.5px #015356; 
      }
      button:hover { filter: brightness(95%); }
      .myBtt {
        width: 100%;
        height: 150px;
        width: 150px;
        border-radius: 150px;
        font-size: 14px;
        margin: 2.5px;
      }
      .divInLineBtts {
        width: 100%;
        max-height: 200px;
        flex: 1; display: flex;
        flex-direction: column;
        align-items: center;
        text-align: center;
      }
      .stateGate {
        font-size: 25px;
      }

      @media (max-height: 640px) {
        .divInLineBtts {
          margin: 25px 0px;
        }
      }
      @media (max-height: 400px) {
        .aling {
          justify-content: flex-start;
        }
      }
    </style>
    <script type='text/javascript'>
          
      const _CLOSED = 0;
      const _OPENING_CLOSING_STOPED = 1;
      let currentStateGate = _CLOSED;

      function getById(id) {
        return document.getElementById(id);
      }

      function initPg() {
         
        getFeedbackGate();
        setInterval(() => {
          getFeedbackGate();
        }, 750);
        getById('divMain').style.display = 'initial';
        getById('tempDiv').style.display = 'none';
      } 

      function getFeedbackGate() {
        const req = new XMLHttpRequest();
        req.open('GET', '/feedbackGate', false );
        // req.open('GET', 'http://localhost:3000/feedbackGate', false )
        req.send();
        if (req.status === 200) {
          const data = JSON.parse(req.responseText);
          currentStateGate = data.feedbackGate;
        }

        currentStateGate === _CLOSED ? getById('gate').innerHTML = 'Estado atual do Portão:<br>Fechado' : getById('gate').innerHTML = 'Estado atual do Portão:<br>Fechando/abrindo ou parado';
        currentStateGate === _CLOSED ? getById('pulseGate').style.backgroundColor = '#53BD38' : getById('pulseGate').style.backgroundColor = '#FF1616';
      }

      function pulseGate() {
        setTimeout(() => {
          const req = new XMLHttpRequest();
          req.open('GET', '/pulse', false );
          // req.open('GET', 'http://localhost:3000/pulse', false )
          req.send();
          if (req.status === 200) {}
        }, 100);
      }

    </script>
  </head>
  <body onload='initPg()'>
    <div class='centralize centerItens aling mainContainer'>
      <div id='tempDiv' class='stateGate centerItens'>
        <p> ... Carregando, aguarde ... </p>
      </div> 
      <div id='divMain' style='display: none'>
        <div class='stateGate centerItens'>
          <p id='gate'></p>
        </div>
        <div class='divInLineBtts centerItens'>
          <button id='pulseGate' class='myBtt' onclick='pulseGate()'>PRESSIONE</button>
        </div>
      </div>
    </div>
  </body>
)rawliteral";

// ----------------------------------------------------------------------------------------- //

#endif

// ----------------------------------------------------------------------------------------- //
