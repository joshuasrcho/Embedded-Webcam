document.querySelector('button').onclick=function(){
    var text = document.querySelector('button').textContent;
    if (text=='Start')
        document.querySelector('button').textContent='Stop';
    else{
        document.querySelector('button').textContent='Start';
    }
}