#ifdef __cplusplus
extern "C" {
#endif
  
#include <ulib/ulib.h>
#include "../gfx/all_gfx.h"

const unsigned char* hiragana_Sprite[16][5] = {
   {hira_a_Sprite,    hira_i_Sprite,        hira_u_Sprite,        hira_e_Sprite,        hira_o_Sprite},
   {hira_ka_Sprite,  hira_ki_Sprite,        hira_ku_Sprite,       hira_ke_Sprite,       hira_ko_Sprite},
  {hira_sa_Sprite,  hira_shi_Sprite,      hira_su_Sprite,       hira_se_Sprite,       hira_so_Sprite},
  {hira_ta_Sprite,  hira_chi_Sprite,      hira_tsu_Sprite,      hira_te_Sprite,       hira_to_Sprite},
  {hira_na_Sprite,  hira_ni_Sprite,       hira_nu_Sprite,       hira_ne_Sprite,       hira_no_Sprite},
  {hira_ha_Sprite,  hira_hi_Sprite,       hira_fu_Sprite,       hira_he_Sprite,       hira_ho_Sprite},
  {hira_ma_Sprite,  hira_mi_Sprite,       hira_mu_Sprite,       hira_me_Sprite,       hira_mo_Sprite},
  {hira_ya_Sprite,  NULL,             hira_yu_Sprite,       NULL,             hira_yo_Sprite},
  {hira_ra_Sprite,  hira_ri_Sprite,       hira_ru_Sprite,       hira_re_Sprite,       hira_ro_Sprite},
  {hira_wa_Sprite,  NULL,             NULL,             NULL,             hira_wo_Sprite},
  {hira_n_Sprite,   NULL,             NULL,             NULL,             NULL},
   {hira_ga_Sprite,   hira_gi_Sprite,       hira_gu_Sprite,       hira_ge_Sprite,       hira_go_Sprite},
  {hira_za_Sprite,  hira_ji_Sprite,       hira_zu_Sprite,       hira_ze_Sprite,       hira_zo_Sprite},
  {hira_da_Sprite,  hira_di_Sprite,       hira_du_Sprite,       hira_de_Sprite,       hira_do_Sprite},
  {hira_ba_Sprite,  hira_bi_Sprite,       hira_bu_Sprite,       hira_be_Sprite,       hira_bo_Sprite},
  {hira_pa_Sprite,  hira_pi_Sprite,       hira_pu_Sprite,       hira_pe_Sprite,       hira_po_Sprite},
};

const short unsigned int* hiragana_Pal[16][5] = {
   {hira_a_Pal,   hira_i_Pal,     hira_u_Pal,   hira_e_Pal,   hira_o_Pal},
   {hira_ka_Pal,  hira_ki_Pal,    hira_ku_Pal,    hira_ke_Pal,  hira_ko_Pal},
  {hira_sa_Pal,   hira_shi_Pal,   hira_su_Pal,  hira_se_Pal,  hira_so_Pal},
  {hira_ta_Pal,   hira_chi_Pal,   hira_tsu_Pal,   hira_te_Pal,  hira_to_Pal},
  {hira_na_Pal,   hira_ni_Pal,  hira_nu_Pal,  hira_ne_Pal,  hira_no_Pal},
  {hira_ha_Pal,   hira_hi_Pal,  hira_fu_Pal,  hira_he_Pal,  hira_ho_Pal},
  {hira_ma_Pal,   hira_mi_Pal,  hira_mu_Pal,  hira_me_Pal,  hira_mo_Pal},
  {hira_ya_Pal,   NULL,       hira_yu_Pal,  NULL,       hira_yo_Pal},
  {hira_ra_Pal,   hira_ri_Pal,  hira_ru_Pal,  hira_re_Pal,  hira_ro_Pal},
  {hira_wa_Pal,   NULL,       NULL,       NULL,       hira_wo_Pal},
  {hira_n_Pal,  NULL,       NULL,       NULL,       NULL},
   {hira_ga_Pal,  hira_gi_Pal,   hira_gu_Pal,   hira_ge_Pal,    hira_go_Pal},
  {hira_za_Pal,   hira_ji_Pal,  hira_zu_Pal,  hira_ze_Pal,  hira_zo_Pal},
  {hira_da_Pal,   hira_di_Pal,  hira_du_Pal,  hira_de_Pal,  hira_do_Pal},
  {hira_ba_Pal,   hira_bi_Pal,  hira_bu_Pal,  hira_be_Pal,  hira_bo_Pal},
  {hira_pa_Pal,   hira_pi_Pal,  hira_pu_Pal,  hira_pe_Pal,  hira_po_Pal},
};

const unsigned char* katakana_Sprite[16][5] =  {
   {kata_a_Sprite,    kata_i_Sprite,        kata_u_Sprite,        kata_e_Sprite,        kata_o_Sprite},
   {kata_ka_Sprite,  kata_ki_Sprite,        kata_ku_Sprite,       kata_ke_Sprite,       kata_ko_Sprite},
  {kata_sa_Sprite,  kata_shi_Sprite,      kata_su_Sprite,       kata_se_Sprite,       kata_so_Sprite},
  {kata_ta_Sprite,  kata_chi_Sprite,      kata_tsu_Sprite,      kata_te_Sprite,       kata_to_Sprite},
  {kata_na_Sprite,  kata_ni_Sprite,       kata_nu_Sprite,       kata_ne_Sprite,       kata_no_Sprite},
  {kata_ha_Sprite,  kata_hi_Sprite,       kata_fu_Sprite,       kata_he_Sprite,       kata_ho_Sprite},
  {kata_ma_Sprite,  kata_mi_Sprite,       kata_mu_Sprite,       kata_me_Sprite,       kata_mo_Sprite},
  {kata_ya_Sprite,  NULL,             kata_yu_Sprite,       NULL,             kata_yo_Sprite},
  {kata_ra_Sprite,  kata_ri_Sprite,       kata_ru_Sprite,       kata_re_Sprite,       kata_ro_Sprite},
  {kata_wa_Sprite,  NULL,             NULL,             NULL,             kata_wo_Sprite},
  {kata_n_Sprite,   NULL,             NULL,             NULL,             NULL},
   {kata_ga_Sprite,   kata_gi_Sprite,       kata_gu_Sprite,       kata_ge_Sprite,       kata_go_Sprite},
  {kata_za_Sprite,  kata_ji_Sprite,       kata_zu_Sprite,       kata_ze_Sprite,       kata_zo_Sprite},
  {kata_da_Sprite,  kata_di_Sprite,       kata_du_Sprite,       kata_de_Sprite,       kata_do_Sprite},
  {kata_ba_Sprite,  kata_bi_Sprite,       kata_bu_Sprite,       kata_be_Sprite,       kata_bo_Sprite},
  {kata_pa_Sprite,  kata_pi_Sprite,       kata_pu_Sprite,       kata_pe_Sprite,       kata_po_Sprite}
};

const short unsigned int* katakana_Pal[16][5] =  {
   {kata_a_Pal,   kata_i_Pal,         kata_u_Pal,       kata_e_Pal,       kata_o_Pal},
   {kata_ka_Pal,  kata_ki_Pal,        kata_ku_Pal,        kata_ke_Pal,      kata_ko_Pal},
  {kata_sa_Pal,   kata_shi_Pal,       kata_su_Pal,      kata_se_Pal,      kata_so_Pal},
  {kata_ta_Pal,   kata_chi_Pal,       kata_tsu_Pal,       kata_te_Pal,      kata_to_Pal},
  {kata_na_Pal,   kata_ni_Pal,      kata_nu_Pal,      kata_ne_Pal,      kata_no_Pal},
  {kata_ha_Pal,   kata_hi_Pal,      kata_fu_Pal,      kata_he_Pal,      kata_ho_Pal},
  {kata_ma_Pal,   kata_mi_Pal,      kata_mu_Pal,      kata_me_Pal,      kata_mo_Pal},
  {kata_ya_Pal,   NULL,           kata_yu_Pal,      NULL,           kata_yo_Pal},
  {kata_ra_Pal,   kata_ri_Pal,      kata_ru_Pal,      kata_re_Pal,      kata_ro_Pal},
  {kata_wa_Pal,   NULL,           NULL,           NULL,           kata_wo_Pal},
  {kata_n_Pal,  NULL,           NULL,           NULL,           NULL},
   {kata_ga_Pal,  kata_gi_Pal,      kata_gu_Pal,        kata_ge_Pal,        kata_go_Pal},
  {kata_za_Pal,   kata_ji_Pal,      kata_zu_Pal,      kata_ze_Pal,      kata_zo_Pal},
  {kata_da_Pal,   kata_di_Pal,      kata_du_Pal,      kata_de_Pal,      kata_do_Pal},
  {kata_ba_Pal,   kata_bi_Pal,      kata_bu_Pal,      kata_be_Pal,      kata_bo_Pal},
  {kata_pa_Pal,   kata_pi_Pal,      kata_pu_Pal,      kata_pe_Pal,      kata_po_Pal},
};

const unsigned char* kanji_Sprite[30][4] =  {
   {kanji_1_Sprite,   kanji_100_Sprite,         kanji_soleil_Sprite,      kanji_an_Sprite},
   {kanji_2_Sprite,   kanji_1000_Sprite,      kanji_lune_Sprite,        kanji_midi_Sprite},
   {kanji_3_Sprite,   kanji_10000_Sprite,       kanji_feu_Sprite,       kanji_devant_Sprite},
   {kanji_4_Sprite,   kanji_p_Sprite,         kanji_eaux_Sprite,        kanji_derriere_Sprite},
   {kanji_5_Sprite,   kanji_m_Sprite,         kanji_arbre_Sprite,     kanji_heure_temps_Sprite},
   {kanji_6_Sprite,   kanji_ami_Sprite,         kanji_or_Sprite,        kanji_intervalle_Sprite},
   {kanji_7_Sprite,   kanji_femme_Sprite,       kanji_terre_Sprite,     kanji_chaque_Sprite},
   {kanji_8_Sprite,   kanji_homme_Sprite,       kanji_origine_Sprite,     kanji_avant_Sprite},
   {kanji_9_Sprite,   kanji_l_homme_Sprite,     kanji_reposer_Sprite,     kanji_maintenant_Sprite},
   {kanji_10_Sprite,    kanji_enfant_Sprite,      kanji_raconter_Sprite,    kanji_quoi_Sprite},
   
   {kanji_dessus_Sprite,      kanji_nom_Sprite,         kanji_vivre_Sprite,     kanji_rond_Sprite},
   {kanji_dessous_Sprite,   kanji_haut_Sprite,      kanji_montagne_Sprite,    kanji_parler_Sprite},
   {kanji_gauche_Sprite,      kanji_petit_Sprite,       kanji_riviere_Sprite,     kanji_ecouter_Sprite},
   {kanji_se_reunir_Sprite,   kanji_moyen_Sprite,       kanji_blanc_Sprite,     kanji_manger_Sprite},
   {kanji_droite_Sprite,      kanji_grand_Sprite,       kanji_ciel_Sprite,      kanji_lire_Sprite},
   {kanji_est_Sprite,       kanji_long_Sprite,      kanji_pluie_Sprite,     kanji_venir_Sprite},
   {kanji_ouest_Sprite,     kanji_moitie_Sprite,      kanji_electricite_Sprite,  kanji_ecrire_Sprite},
   {kanji_sud_Sprite,       kanji_partager_Sprite,    kanji_air_Sprite,       kanji_regarder_Sprite},
   {kanji_nord_Sprite,      kanji_etudier_Sprite,     kanji_automobile_Sprite,    kanji_aller_Sprite},
   {kanji_exterieur_Sprite,   kanji_ecole_Sprite,       kanji_pays_Sprite,        kanji_sortir_Sprite},
   
   {kanji_entrer_Sprite,        kanji_communaute_Sprite,      kanji_boire_Sprite,   NULL},
   {kanji_bouche_Sprite,        kanji_creux_Sprite,           kanji_gare_Sprite,      NULL},
   {kanji_vieux_Sprite,       kanji_se_mettre_debout_Sprite,   kanji_poisson_Sprite,  NULL},
   {kanji_nombreux_Sprite,      kanji_oreille_Sprite,         NULL,             NULL},
   {kanji_calme_Sprite,       kanji_fleur_Sprite,           NULL,             NULL},
   {kanji_peu_nombreux_Sprite,    kanji_dire_Sprite,          NULL,             NULL},
   {kanji_magasin_Sprite,     kanji_acheter_Sprite,         NULL,             NULL},
   {kanji_main_Sprite,        kanji_pieds_Sprite,           NULL,             NULL},
   {kanji_neuf_Sprite,        kanji_semaine_Sprite,         NULL,             NULL},
   {kanji_yeux_Sprite,        kanji_chemin_Sprite,          NULL,             NULL}
};

const short unsigned int* kanji_Pal[30][4] =  {
   {kanji_1_Pal,    kanji_100_Pal,        kanji_soleil_Pal,     kanji_an_Pal},
   {kanji_2_Pal,    kanji_1000_Pal,       kanji_lune_Pal,       kanji_midi_Pal},
   {kanji_3_Pal,    kanji_10000_Pal,      kanji_feu_Pal,        kanji_devant_Pal},
   {kanji_4_Pal,    kanji_p_Pal,        kanji_eaux_Pal,       kanji_derriere_Pal},
   {kanji_5_Pal,    kanji_m_Pal,        kanji_arbre_Pal,      kanji_heure_temps_Pal},
   {kanji_6_Pal,    kanji_ami_Pal,        kanji_or_Pal,       kanji_intervalle_Pal},
   {kanji_7_Pal,    kanji_femme_Pal,      kanji_terre_Pal,      kanji_chaque_Pal},
   {kanji_8_Pal,    kanji_homme_Pal,      kanji_origine_Pal,      kanji_avant_Pal},
   {kanji_9_Pal,    kanji_l_homme_Pal,    kanji_reposer_Pal,      kanji_maintenant_Pal},
   {kanji_10_Pal,   kanji_enfant_Pal,       kanji_raconter_Pal,   kanji_quoi_Pal},
   
   {kanji_dessus_Pal,     kanji_nom_Pal,        kanji_vivre_Pal,      kanji_rond_Pal},
   {kanji_dessous_Pal,    kanji_haut_Pal,       kanji_montagne_Pal,   kanji_parler_Pal},
   {kanji_gauche_Pal,     kanji_petit_Pal,      kanji_riviere_Pal,      kanji_ecouter_Pal},
   {kanji_se_reunir_Pal,    kanji_moyen_Pal,      kanji_blanc_Pal,      kanji_manger_Pal},
   {kanji_droite_Pal,     kanji_grand_Pal,      kanji_ciel_Pal,     kanji_lire_Pal},
   {kanji_est_Pal,        kanji_long_Pal,       kanji_pluie_Pal,      kanji_venir_Pal},
   {kanji_ouest_Pal,      kanji_moitie_Pal,       kanji_electricite_Pal,  kanji_ecrire_Pal},
   {kanji_sud_Pal,        kanji_partager_Pal,     kanji_air_Pal,        kanji_regarder_Pal},
   {kanji_nord_Pal,     kanji_etudier_Pal,    kanji_automobile_Pal,   kanji_aller_Pal},
   {kanji_exterieur_Pal,    kanji_ecole_Pal,      kanji_pays_Pal,       kanji_sortir_Pal},
   
   {kanji_entrer_Pal,       kanji_communaute_Pal,       kanji_boire_Pal,    NULL},
   {kanji_bouche_Pal,       kanji_creux_Pal,          kanji_gare_Pal,     NULL},
   {kanji_vieux_Pal,        kanji_se_mettre_debout_Pal,   kanji_poisson_Pal,  NULL},
   {kanji_nombreux_Pal,     kanji_oreille_Pal,        NULL,           NULL},
   {kanji_calme_Pal,        kanji_fleur_Pal,          NULL,           NULL},
   {kanji_peu_nombreux_Pal,   kanji_dire_Pal,           NULL,           NULL},
   {kanji_magasin_Pal,      kanji_acheter_Pal,        NULL,           NULL},
   {kanji_main_Pal,       kanji_pieds_Pal,          NULL,           NULL},
   {kanji_neuf_Pal,       kanji_semaine_Pal,        NULL,           NULL},
   {kanji_yeux_Pal,       kanji_chemin_Pal,           NULL,           NULL}
};

#ifdef __cplusplus
}
#endif

