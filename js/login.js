document.getElementById('loginForm').addEventListener('submit', function(event) {
    event.preventDefault();

    const email = document.getElementById('email');
    const password = document.getElementById('password');
    const emailError = document.getElementById('emailError');
    const passwordError = document.getElementById('passwordError');
    const feedback = document.getElementById('feedback');

    emailError.textContent = '';
    passwordError.textContent = '';
    feedback.textContent = '';

    // Validações
    if (!email.value) {
        emailError.textContent = 'O e-mail é obrigatório.';
        return;
    }
    if (!password.value) {
        passwordError.textContent = 'A senha é obrigatória.';
        return;
    }

    if (email.value === "admfacul@gmail.com" && password.value === "123") {
        feedback.textContent = "Login válido! Redirecionando...";
        feedback.style.color = "green";
        setTimeout(() => {
            window.location.href = "index.html";
        }, 1500);
    } else {
        feedback.textContent = "E-mail ou senha incorretos!";
        feedback.style.color = "red";
        
        email.value = '';
        password.value = '';
        
        email.focus();
    }
});