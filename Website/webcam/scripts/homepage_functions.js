document.querySelector('img').onclick=function(){
    var text = document.querySelector('h1').textContent;
    if (text=='Home Automation')
        document.querySelector('h1').textContent='HI';
    else{
        document.querySelector('h1').textContent='Home Automation';
    }
}