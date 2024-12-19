document.addEventListener("DOMContentLoaded", () => {
    const footerHTML = `
        <footer class="text-center">
            <div class="container">
                <p>Realizzato da Niccolò Grappeggia - Classe 5°F</p>
                <p>
                    <a href="https://github.com/GrappeggiaNiccolo/TPSI/tree/main/5%C2%B0F/Bootstrap%20websites/Socket"
                        class="text-white" target="_blank">Github Repository</a>
                </p>
            </div>
        </footer>
    `;
    document.getElementById("footer-placeholder").innerHTML = footerHTML;
});
