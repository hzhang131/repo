var MyVar;
function randomplacement(s){
    var elem = document.querySelector(".text-pos");
    var fullHeight = window.innerHeight;
    var fullWidth = window.innerWidth;
    var random_num1 = Math.round(Math.random() * 100);
    var random_num2 = Math.round(Math.random() * 100);
    while (random_num1 >= 78) random_num1 = random_num1 - 10;
    while (random_num2 >= 78) random_num2 = random_num2 - 10;
    elem.style.top = random_num1.toString() + "vh";
    console.log(random_num1);
    console.log(random_num2);
    elem.style.left = random_num2.toString() + "vw";
    document.write(s);
}

function place_after_1500ms(s){
    myVar = setInterval(randomplacement(s), 1500);
}

function write(string){
    var elem = document.querySelector(".text-pos");
    elem.style.top = "22%";
    elem.style.left = "14%";
    document.write(string);

}