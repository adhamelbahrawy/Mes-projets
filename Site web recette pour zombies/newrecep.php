<?php include "sql.php" ?>
<?php include "Back/Redondances/head.php" ?>
    <body>
        </div>
        <form method="POST" id="recepform">
            <div>
                <label for="recepname">Recepie name*</label>
                <input
                    type="text"
                    id="recepname" 
                    name="recepname" 
                    placeholder="Zombie Eyes"
                    aria-reqquired="true"
                    aria-labelledby="recepname">
            </div>
            <div>
                <label for="first">First name*</label>
                <input 
                    type="text" 
                    id="first" 
                    name="first" 
                    placeholder="John"
                    aria-reqquired="true"
                    aria-labelledby="first">
            </div>
            <div>
                <label for="last">Last name*</label>
                <input 
                    type="text" 
                    id="last" 
                    name="last" 
                    placeholder="Smith"
                    aria-reqquired="true"
                    aria-labelledby="last">
            </div>
            <div>
                <label for="recep">Instructions*</label>
                <textarea 
                    name="recep" 
                    id="recep" 
                    cols="30" 
                    rows="10" 
                    placeholder="Peel and deseed lychee (use canned lychee if you like), stuff with jam/jelly and a black cherry."
                    aria-reqquired="true"
                    aria-labelledby="recep"></textarea>
            </div>
            <button type="submit" id="subform">Submit recepie</button>
        </form>
        <?php include "Back/Redondances/footer.php" ?>
    <body>
    <script src="Front/veriform.js"></script>
</html>
