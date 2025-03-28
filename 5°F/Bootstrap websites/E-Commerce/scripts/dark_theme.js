(() => {
   'use strict';

   // Funzione per ottenere il tema salvato nel localStorage
   const getStoredTheme = () => localStorage.getItem('theme');

   // Funzione per salvare il tema nel localStorage
   const setStoredTheme = theme => localStorage.setItem('theme', theme);

   // Funzione per determinare il tema preferito (da localStorage o sistema)
   const getPreferredTheme = () => {
      const storedTheme = getStoredTheme();
      if (storedTheme) {
         return storedTheme;
      }
      // Rileva la preferenza del sistema (scuro o chiaro)
      return window.matchMedia('(prefers-color-scheme: dark)').matches ? 'dark' : 'light';
   };

   // Funzione per applicare il tema (dark o light) all'elemento document
   const setTheme = theme => {
      document.documentElement.setAttribute('data-bs-theme', theme);

      // Modifica classi del body
      if (theme === 'dark') {
         document.body.classList.add('dark-mode');
      } else {
         document.body.classList.remove('dark-mode');
      }

      // Modifica classi della navbar
      const navbar = document.querySelector('.navbar');
      if (navbar) {
         if (theme === 'dark') {
            navbar.classList.remove('navbar-light', 'bg-light');
            navbar.classList.add('navbar-dark', 'bg-dark');
         } else {
            navbar.classList.remove('navbar-dark', 'bg-dark');
            navbar.classList.add('navbar-light', 'bg-light');
         }
      }

      // Modifica classi del footer
      const footer = document.querySelector('footer');
      if (footer) {
         if (theme === 'dark') {
            footer.classList.remove('bg-light', 'text-dark');
            footer.classList.add('bg-dark', 'text-white');
         } else {
            footer.classList.remove('bg-dark', 'text-white');
            footer.classList.add('bg-light', 'text-dark');
         }
      }
   };

   // Funzione per aggiornare il bottone e mostrare l'icona del tema attivo
   const showActiveTheme = (theme) => {
      const themeSwitcher = document.querySelector('#bd-theme');
      const activeThemeIcon = themeSwitcher.querySelector('i');

      if (theme === 'dark') {
         activeThemeIcon.classList.replace('bi-sun-fill', 'bi-moon-fill'); // Cambio icona a luna
      } else {
         activeThemeIcon.classList.replace('bi-moon-fill', 'bi-sun-fill'); // Cambio icona a sole
      }
   };

   // Aggiungi l'evento per il cambio di tema tramite il bottone
   window.addEventListener('DOMContentLoaded', () => {
      const currentTheme = getPreferredTheme();
      setTheme(currentTheme);
      showActiveTheme(currentTheme);

      // Aggiungi evento al bottone per cambiare tema
      document.querySelector('#bd-theme').addEventListener('click', () => {
         // Alterna tra 'light' e 'dark'
         const newTheme = (document.documentElement.getAttribute('data-bs-theme') === 'light' ? 'dark' : 'light');
         setStoredTheme(newTheme); // Salva il nuovo tema
         setTheme(newTheme); // Applica il nuovo tema
         showActiveTheme(newTheme); // Cambia l'icona del bottone
      });
   });

   // Ascolta i cambiamenti di preferenza di tema nel sistema
   window.matchMedia('(prefers-color-scheme: dark)').addEventListener('change', () => {
      const storedTheme = getStoredTheme();
      if (storedTheme !== 'light' && storedTheme !== 'dark') {
         setTheme(getPreferredTheme());
      }
   });
})();
