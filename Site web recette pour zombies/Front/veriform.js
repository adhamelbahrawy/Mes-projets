const inpNames = /^[\S]{1,50}$/;
const inpNamesVerif = function()
{
    if(this.value.match(inpNames) == null)
    {
        this.classList.add("errorinput");
        this.previousElementSibling.classList.add("errorinput");
        hasError = true;
    }
    else
    {        
        this.classList.remove("errorinput");
        this.previousElementSibling.classList.remove("errorinput");
        hasError = false;
    }
}

var sub = document.getElementById("subform");
sub.addEventListener("click", function(event)
    {
        event.preventDefault();

        let hasError = false;
        let inpRecepName = document.getElementById("recepname");
        let inpFirst = document.getElementById("first");
        let inpLast = document.getElementById("last");
        let inpRecep = document.getElementById("recep");

        if(inpRecepName.value.match(/^([a-zàâçéèêëîïôûùüÿñæœ0-9-]+ )*[a-zàâçéèêëîïôûùüÿñæœ0-9-]{1,50}$/i) == null)
        {
            inpRecepName.classList.add("errorinput");
            inpRecepName.previousElementSibling.classList.add("errorinput");
            hasError = true;
        }
        inpRecepName.addEventListener("input", function()
        {
            if(this.value.match(/^([a-zàâçéèêëîïôûùüÿñæœ0-9-]+ )*[a-zàâçéèêëîïôûùüÿñæœ0-9-]{1,50}$/i) == null) //pas de gâchi d'espace
            {
                this.classList.add("errorinput");
                this.previousElementSibling.classList.add("errorinput");
                hasError = true;
            }
            else
            {        
                this.classList.remove("errorinput");
                this.previousElementSibling.classList.remove("errorinput");
                hasError = false;
            }
        });
    
        if(inpFirst.value.match(inpNames) == null)
        {
            inpFirst.classList.add("errorinput");
            inpFirst.previousElementSibling.classList.add("errorinput");
            hasError = true;
        }
        inpFirst.addEventListener("input", inpNamesVerif);

        if(inpLast.value.match(inpNames) == null)
        {
            inpLast.classList.add("errorinput");
            inpLast.previousElementSibling.classList.add("errorinput");
            hasError = true;
        }
        inpLast.addEventListener("input", inpNamesVerif);

        if(inpRecep.value == "")
        {
            inpRecep.classList.add("errorinput");
            inpRecep.previousElementSibling.classList.add("errorinput");
            hasError = true;
        }
        inpRecep.addEventListener("input", function()
        {
            if(this.value == "") 
            {
                this.classList.add("errorinput");
                this.previousElementSibling.classList.add("errorinput");
                hasError = true;
            }
            else
            {        
                this.classList.remove("errorinput");
                this.previousElementSibling.classList.remove("errorinput");
                hasError = false;
            }
        });
        if(!hasError)
        {
            document.getElementById("recepform").submit();
        }
    });