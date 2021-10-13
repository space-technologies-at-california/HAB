import auth from '@planet/client/api/auth';
const STORAGE_KEY = 'planet-token-4ux3ak8eqtypr4dh';
const sessionStorage = window.sessionStorage;

function login() {
 const email = document.getElementById('email')
 const password = document.getElementById('password')
 const response = auth.login(email.value, password.value).then(() => {
   if (auth.getToken()) {
     sessionStorage.setItem(STORAGE_KEY, auth.getToken());
     email.value = '';
     password.value = '';
     window.location.href = '/';
   }
 }).catch(error => {
   password.value = '';
   document.getElementById('error').style.visibility = 'visible';
 })
}
function logout() {
 auth.logout()
 sessionStorage.removeItem(STORAGE_KEY);
 window.location.href = '/login.html';
}
export function getPlanetApiKey() {
 return auth.getKey();
}
window.auth = auth;
window.login = login;
window.logout = logout;
// Init page
const storedToken = sessionStorage.getItem(STORAGE_KEY);
if (storedToken) {
 auth.setToken(storedToken)
} else if (window.location.pathname != '/login.html') {
 window.location.href = '/login.html';
}
