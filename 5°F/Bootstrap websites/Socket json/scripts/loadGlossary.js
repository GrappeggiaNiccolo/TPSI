document.addEventListener("DOMContentLoaded", () => {
    const loadGlossaryData = async () => {
        try {
            const response = await fetch("json/glossaryContent.json");
            const glossaryData = await response.json();

            // Funzione per creare una sezione HTML
            const createSection = (content, containerId) => {
                const container = document.getElementById(containerId);
                if (!container) return;

                const titleElement = document.createElement("h1");
                titleElement.className = "display-5";
                titleElement.textContent = content.title;

                const descElement = document.createElement("p");
                descElement.className = "lead text-muted";
                descElement.textContent = content.description;

                container.appendChild(titleElement);
                container.appendChild(descElement);
            };

            // Funzione per creare l'elenco dei termini
            const createGlossaryList = (terms, containerId) => {
                const container = document.getElementById(containerId);
                if (!container) return;

                terms.forEach(termData => {
                    const item = document.createElement("a");
                    item.href = "#";
                    item.className = "list-group-item list-group-item-action";

                    const termElement = document.createElement("h5");
                    termElement.className = "mb-1";
                    termElement.textContent = termData.term;

                    const definitionElement = document.createElement("p");
                    definitionElement.className = "mb-1";
                    definitionElement.textContent = termData.definition;

                    item.appendChild(termElement);
                    item.appendChild(definitionElement);
                    container.appendChild(item);
                });
            };

            // Popolamento della pagina
            createSection(glossaryData.titleSection, "title-section");
            createGlossaryList(glossaryData.terms, "glossary-list");
        } catch (error) {
            console.error("Errore nel caricamento del glossario:", error);
        }
    };

    loadGlossaryData();
});
