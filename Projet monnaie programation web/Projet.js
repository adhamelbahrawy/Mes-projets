function alea(min,max){
    min = Math.ceil(min);
    max = Math.floor(max);
    brouzoufs = Math.floor(Math.random() * (max - min)) + min; 
    cents = Math.floor(Math.random() * (10 - 0)) / 10.0; 
    return brouzoufs+cents;
}
var service_en_cours = true;

function init()
{
    
    var numdue = alea(0,100);
    numdue = numdue.toFixed(1);
    document.getElementById("due").textContent = numdue;
    var paye = Math.ceil(numdue / 10) * 10;
    document.getElementById("payed").textContent = paye;
    document.getElementById("status").textContent = "non traité";
    document.getElementById("status").style.color = "black";
    service_en_cours = true;
    if(service_en_cours == true)
    {
        document.getElementById("next").style.color = "darkgray";
        document.getElementById("next").style.fontStyle = "italic";
        document.getElementById("next").value = "Service en cours";
    }
    else
    {
        document.getElementById("next").style.color = "black";
        document.getElementById("next").style.fontStyle = "normal";
        document.getElementById("next").value = "Servir le prochain client";
    }
}

init();

var statbout = document.getElementById("openclose");

function caissestat()
{
    if(statbout.value === "Ouvrir le tiroir caisse")
    {
        document.getElementById("caisse").style.display="flex";
        statbout.value = "Fermer le tiroir caisse";
    }
    else
    {
        document.getElementById("caisse").style.display="none";
        statbout.value = "Ouvrir le tiroir caisse";
    }
}
statbout.addEventListener("click",caissestat);

function spanadd(n)
{
    var x = Number.parseFloat(document.getElementById("rest").textContent);
    var res = (x+n);
    res = res.toFixed(2)
    document.getElementById("rest").textContent = res;
}

document.getElementById("20").addEventListener("click", function(){spanadd(20)});
document.getElementById("10").addEventListener("click", function(){spanadd(10)});
document.getElementById("5").addEventListener("click", function(){spanadd(5)});
document.getElementById("2").addEventListener("click", function(){spanadd(2)});
document.getElementById("1").addEventListener("click", function(){spanadd(1)});
document.getElementById("0.5").addEventListener("click", function(){spanadd(0.50)});
document.getElementById("0.2").addEventListener("click", function(){spanadd(0.20)});
document.getElementById("0.1").addEventListener("click", function(){spanadd(0.10)});

function verifmonnaie()
{
    var m = Number.parseFloat(document.getElementById("rest").textContent);
    m = m.toFixed(2);
    var p = Number.parseFloat(document.getElementById("payed").textContent);
    p = p.toFixed(2);
    var d = Number.parseFloat(document.getElementById("due").textContent);
    d = d.toFixed(2);
    var r = Number.parseInt(document.getElementById("rate").textContent);
    var c = Number.parseInt(document.getElementById("client").textContent);
    if (((p-d).toFixed(2)) < m)
    {
        document.getElementById("rate").textContent = (r+1);
        document.getElementById("status").textContent = "Rendu plus que nécessaire";
        document.getElementById("status").style.color = "red";
    }
    else if (((p-d).toFixed(2)) > m)
    {
        document.getElementById("rate").textContent = (r+1);
        document.getElementById("status").textContent = "Il manque de la monnaie !";
        document.getElementById("status").style.color = "red";
    }
    else
    {
        document.getElementById("status").textContent = "Le compte est bon !";
        document.getElementById("status").style.color = "green";
    }
    document.getElementById("client").textContent = c+1;
    document.getElementById("next").style.fontStyle = "normal";
    document.getElementById("next").style.color = "black";
    document.getElementById("next").value = "Servir le prochain client";
    document.getElementById("rest").textContent = "0.00";
    service_en_cours = false;
}

document.getElementById("return").addEventListener("click",verifmonnaie)

function nextclient()
{
    if (service_en_cours == false)
    {
       init()
    }
}
document.getElementById("next").addEventListener("click",nextclient)




