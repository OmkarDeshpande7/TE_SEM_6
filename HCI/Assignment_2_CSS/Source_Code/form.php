<!DOCTYPE html>
<html>

<head>
    <title>Enrollment Form</title>

</head>
<style type="text/css">
    input {
        width: 45%;
        margin-bottom: 20px;
        margin-top: 7px;
        background: transparent;
        border: none;
        color: white;
        border-bottom: 2px solid lightgreen;
    }
    
    input:hover {
        transition: 0.2s;
        border-bottom: 2px solid white;
    }
    
    button {
        width: 20%;
        background-color: #ffb3b3;
        color: black;
        height: 30px;
        border-radius: 10px;
        border: none;
    }
    
    input[type=submit] {
        width: 20%;
        background-color: #ffb3b3;
        color: black;
        height: 30px;
        border-radius: 10px;
        border: none;
    }
    
    input[type=date]::-webkit-inner-spin-button,
    input[type=number]::-webkit-outer-spin-button {
        -webkit-appearance: none;
        margin: 0;
    }
    
    input[type=submit]:hover {
        background-color: green;
        transition: .2s;
    }
    
    input[type=radio] {
        width: 5%;
    }
    
    select {
        width: 20%;
        padding-left: 8%;
    }
    
    label {
        margin-top: 9px;
        font-weight: bold;
        font-size: 22px;
        color: white;
    }
    
     ::placeholder {
        color: white;
        opacity: 0.6;
    }
    
    input:focus,
    select:focus,
    textarea:focus,
    button:focus {
        outline: none;
    }
</style>

<body style="background-image: url(bg3.jpg);background-size: cover;">
<?php
// define variables and set to empty values
$nameErr = $emailErr = $genderErr = $passwordErr = $phoneErr = "";
$name = $email = $password = $phone = $website = "";
if ($_SERVER["REQUEST_METHOD"] == "POST") {
  
  if (empty($_POST["email"])) {
    $emailErr = "Email is required";
  } else {
    $email = test_input($_POST["email"]);
    // check if e-mail address is well-formed
    if (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
      $emailErr = "Invalid email format";
    }
  }
    
  if (empty($_POST["phone"])) {
    $phoneErr = "Phone is required";
  } else {
    $phone = test_input($_POST["Phone"]);
  }


if (empty($_POST["password"])) {
    $passwordErr = "Password is required";
  } else {
    $password = test_input($_POST["password"]);
  }



  if (empty($_POST["gender"])) {
    $genderErr = "Gender is required";
  } else {
    $gender = test_input($_POST["gender"]);
  }
}

function test_input($data) {
  $data = trim($data);
  $data = stripslashes($data);
  $data = htmlspecialchars($data);
  return $data;
}
?>
    <h1 style="color: white;font-size: 50px;" align="center">Enter Your Details !</h1>
    <div style="margin-left: 25% ;width: 50%;">
        <form method="post" action="test.php" >

            <div style=" border: 2px solid white;padding: 20px">
                <label for="email">Email : </label><br>
                <input maxlength="20" ondblclick="return newfunc(this);" autocomplete="off" placeholder="Enter email *" onkeyup="validateEmail(this)" type="text" id="email" name="email"><br>
                <span style="color:red;"> <?php echo $emailErr;?></span><br>

                <label for="phone">Phone Number : </label><br>
                <input maxlength="10" ondblclick="return newfunc(this);" autocomplete="off" placeholder="Enter Mobile number *" id="phone" type="tel" name="phone"><br>
                <span style="color:red;"> <?php echo $phoneErr;?></span><br>


                <label for="password">Password : </label><br>
                <input maxlength="15" ondblclick="return newfunc(this);" autocomplete="off" placeholder="Enter password *" type="password" id="password" name="password"><br>
                <span style="color:red;"> <?php echo $passwordErr;?></span><br>


                <button type="button" id="btn1">RESET</button>
            </div>

            <div style="border: 2px solid white;padding: 20px;margin-top: 20px">
                <div style="width: 50%; float: left">
                    <label for="fname">First Name : </label><br>
                    <input style="width: 95%" maxlength="20" ondblclick="return newfunc(this);" autocomplete="off" placeholder="Enter first name..." id="fname" type="text" name="fname"><br>
                </div>
                <div style="width:50%;float: right">
                    <label for="lname">Last Name : </label><br>
                    <input style="width: 95%" maxlength="20" ondblclick="return newfunc(this);" autocomplete="off" placeholder="Enter last name..." id="lname" type="text" name="lname"><br>
                </div>
                <br>
                <label for="address"> Address : </label><br>
                <input maxlength="30" ondblclick="return newfunc(this);" autocomplete="off" placeholder="Enter Full address..." id="address" type="text" name="address"><br>

                <label for="Pincode">Pincode : </label><br>
                <input maxlength="6" ondblclick="return newfunc(this);" autocomplete="off" placeholder="Enter Pincode..." pattern="^\d{6}" id="pincode" type="tel" name="Pincode"><br>

                <label for="gender">Gender : </label><br>
                <input ondblclick="return newfunc(this);" autocomplete="off" id="radio1" type="radio" name="gender" checked>male
                <input ondblclick="return newfunc(this);" autocomplete="off" id="radio2" type="radio" name="gender">female<br>
                <label for="dob">DOB : </label><br>
                <input ondblclick="return newfunc(this);" autocomplete="off" id="dob" type="date" name="dob" checked>
                <h3 style="color: white;">Please Enter Your Qualification : </h3>

                <select ondblclick="return newfunc(this);" id="qualification">
		<option>UG</option>
		<option>PG</option>
		<option>SSC</option>
		<option>HSC</option>
	</select><br>

                <button type="button" style="margin-top: 20px" id="btn2">RESET</button>
            </div>

            <button class="prevbtn" style="margin-top: 20px;" id="submitbtn" type="submit" name="submit">Submit</button>
            <button type="button" style="margin-top: 20px" id="btn3">Reset</button>

        </form>
    </div>


    <audio id="player">
		<source src="beep.wav" type="audio/wav">
	</audio><br>




    <script>
        function playAudio() {
            document.getElementById("player").play();
        } 



        document.getElementById("btn1").onclick = function() {
            todo1();
        }



        function todo1() {
            document.getElementById("email").value = "";
            document.getElementById("phone").value = "";
            document.getElementById("password").value = "";

        }


        document.getElementById("btn2").onclick = function() {
            todo2();
        }




        function todo2() {
            document.getElementById("fname").value = "";
            document.getElementById("mname").value = "";
            document.getElementById("lname").value = "";
            document.getElementById("qualification").value = "UG";
            document.getElementById("pincode").value = "";
            document.getElementById("radio1").checked = false;
            document.getElementById("radio2").checked = false;
        }

        document.getElementById("btn3").onclick = function() {
            todo1();
            todo2();
        }

        function newfunc(here) {
            here.value = "";
        }

        document.getElementById("dob").onblur = function() {
            var d1 = new Date();
            var d2 = new Date(document.getElementById("dob").value);
            var timeDiff = d2.getTime() - d1.getTime();
            var diff = timeDiff / (1000 * 3600 * 24);

            var value = parseInt(-1 * 365 * 14);

            if (parseInt(diff) <= 0) {

                if (parseInt(diff) < parseInt(value)) {
                    window.location.href = "successful.html";
                } else {
                    alert("Cannot submit response ! user is minor !");
                }
            } else {
                alert("Wrong Date of birth !");
            }

        }
    </script>
</body>



</html>