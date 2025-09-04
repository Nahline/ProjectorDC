
function openPopup() {
    document.getElementById('popup').style.display = 'block';
}

function closePopup() {
    document.getElementById('popup').style.display = 'none';
}

// Close when clicking outside
window.onclick = function (event) {
    if (event.target == document.getElementById('popup')) {
        closePopup();
    }
}